/*
 * descr: class definition for Tilemap game structure container
 * author: Henry Dikeman
 */

// stdlib headers
#include <stdbool.h>
#include <iostream>
#include <memory>

// externlib headers
#include <SDL.h>

// internlib headers
#include "Static.h"
#include "Sprite.h"
#include "Tile.h"

#ifndef TILEMAP_H
#define TILEMAP_H

class Tilemap {
    private:
        int map_height, map_width, grid_spacing;
        Tile* map;
    public:
        // constructors
        Tilemap();
        Tilemap(int width, int height, int spacing);

        // destructor
        ~Tilemap();

        // tile getters
        Tile& operator()(int x, int y) { return map[x*map_width + y]; }
        std::shared_ptr<Sprite>& sprite(int x, int y) { return map[x*map_width + y].sprite_layer; }
        std::shared_ptr<Static>& statics(int x, int y) { return map[x*map_width + y].static_layer; }
        std::shared_ptr<Static>& background(int x, int y) { return map[x*map_width + y].background_layer; }

        // map getters
        int& height() { return map_height; }
        int& width() { return map_width; }
        int& spacing() { return grid_spacing; }

        // entity shift methods
        bool sprite_left(int x, int y) { return move_sprite(x, y, x-1, y); sprite(x,y)->direction() = SpriteDirection::LEFT; }
        bool sprite_right(int x, int y) { return move_sprite(x, y, x+1, y); sprite(x,y)->direction() = SpriteDirection::RIGHT; }
        bool sprite_up(int x, int y) { return move_sprite(x, y, x, y-1); sprite(x,y)->direction() = SpriteDirection::UP; }
        bool sprite_down(int x, int y) { return move_sprite(x, y, x, y+1); sprite(x,y)->direction() = SpriteDirection::DOWN; }
        bool move_sprite(int start_x, int start_y, int end_x, int end_y);

        // Sprite rendering functions
        void render_sprites(SDL_Renderer* renderer);
        void draw(SDL_Renderer* renderer, int x, int y);

        // status methods
        bool is_occupied(int x, int y);
        bool is_occupied(const std::shared_ptr<Sprite>& spr);
        bool validate_coords(int x, int y) const;
};

// default constructor with default size and width
Tilemap::Tilemap() : 
    map_height(64), 
    map_width(64), 
    grid_spacing(32) {
        // allocate map array
        map = new Tile[map_height * map_width];
        // print new ptr address
        std::cout << "new Tile array: ";
        std::cout << map << std::endl;
    }

// constructor with parametrized width and height
Tilemap::Tilemap(int width, int height, int spacing) : 
    map_height(height), 
    map_width(width),
    grid_spacing(spacing) {
        // allocate map array
        map = new Tile[map_height * map_width];
        // print new ptr address
        std::cout << "new Tile array: ";
        std::cout << map << std::endl;
    }

// destructor
Tilemap::~Tilemap() {
    // print new ptr address
    std::cout << "free Tile array: ";
    std::cout << map << std::endl;
    // deallocate map array
    delete[] map;
}

// generic move sprite method
bool Tilemap::move_sprite(int start_x, int start_y, int end_x, int end_y) {
    if (validate_coords(start_x, start_y) && validate_coords(end_x, end_y)) {
            if (is_occupied(start_x, start_y) && !is_occupied(end_x, end_y)) {
                // adjust position
                this->sprite(start_x, start_y)->x() = end_x;
                this->sprite(start_x, start_y)->y() = end_y;
                // move in map
                sprite(end_x, end_y) = std::move(sprite(start_x, start_y));
                // return success
                return true;
            }
    }
    return false;
}

void Tilemap::render_sprites(SDL_Renderer* renderer) {
    // draw each spot on the map
    for (int i = 0; i < this->width(); i++) {
        for (int j = 0; j < this->height(); j++) {
            this->draw(renderer, i, j);
        }
    }
}

// draw Tilemap contents to window
void Tilemap::draw(SDL_Renderer* renderer, int x, int y) {
    // check validity of coordinates
    if (validate_coords(x,y)) {
        // draw sprite if initialized
        if (is_occupied(sprite(x,y))) {
            SDL_RenderCopy(renderer, sprite(x,y)->get_texture(), sprite(x,y)->get_srcrect(), sprite(x,y)->get_dstrect());
        }
    }
}

// test whether given location is occupied
bool Tilemap::is_occupied(int x, int y) {
    return this->sprite(x,y) != nullptr;
}

// occupied test using passed Drawable
bool Tilemap::is_occupied(const std::shared_ptr<Sprite>& spr) {
    return spr != nullptr;
}

// test whether a given pair of coordinates are valid
bool Tilemap::validate_coords(int x, int y) const {
    return x >= 0 && x < map_width && y >= 0 && y < map_height;
}

#endif

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
        int map_height, map_width;
        int center_x, center_y;
        int grid_spacing;
        int vp_width, vp_height;
        SDL_Texture* bg_texture;
        Tile* map;
    public:
        // constructors
        Tilemap();
        Tilemap(int width, int height, int spacing, int vp_width, int vp_height);

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
        SDL_Texture*& background_texture() { return bg_texture; } 
        
        // center setters
        void set_center(int center_x, int center_y) {
            this->center_x = center_x;
            this->center_y = center_y;
        }

        // entity shift methods
        bool sprite_left(int x, int y) { 
            if (sprite(x,y)->direction() != SpriteDirection::LEFT) {
                sprite(x,y)->direction() = SpriteDirection::LEFT; 
                return true;
            }
            return move_sprite(x, y, x-1, y); 
        }
        bool sprite_right(int x, int y) {
            if (sprite(x,y)->direction() != SpriteDirection::RIGHT) {
                sprite(x,y)->direction() = SpriteDirection::RIGHT; 
                return true;
            }
            return move_sprite(x, y, x+1, y); 
        }
        bool sprite_up(int x, int y) { 
            if (sprite(x,y)->direction() != SpriteDirection::UP) {
                sprite(x,y)->direction() = SpriteDirection::UP; 
                return true;
            }
            return move_sprite(x, y, x, y-1); 
        }
        bool sprite_down(int x, int y) {
            if (sprite(x,y)->direction() != SpriteDirection::DOWN) {
                sprite(x,y)->direction() = SpriteDirection::DOWN;
                return true;
            }
            return move_sprite(x, y, x, y+1); 
        }
        bool move_sprite(int start_x, int start_y, int end_x, int end_y);

        // rendering functions
        void render_background(SDL_Renderer* renderer);
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
    grid_spacing(32),
    vp_width(10),
    vp_height(10) {
        // allocate map array
        map = new Tile[map_height * map_width];
        // print new ptr address
        std::cout << "new Tile array: ";
        std::cout << map << std::endl;
    }

// constructor with parametrized width and height
Tilemap::Tilemap(int width, int height, int spacing, int vp_width, int vp_height) : 
    map_height(height), 
    map_width(width),
    grid_spacing(spacing),
    vp_width(vp_width),
    vp_height(vp_height) {
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

    // destroy background texture if created
    if (bg_texture) { SDL_DestroyTexture(bg_texture); }
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

void Tilemap::render_background(SDL_Renderer* renderer) {
    // determine what portion of background texture to be rendered
    int dst_x = center_x > vp_width/2 ? 0 : vp_width/2-center_x;
    int dst_y = center_y > vp_height/2 ? 0 : vp_height/2-center_y;
    int src_x = center_x < vp_width/2 ? 0 : center_x-vp_width/2;
    int src_y = center_y < vp_height/2 ? 0 : center_y - vp_height/2;
    int rect_w = center_x + vp_width/2 < map_width ? vp_width : (vp_width/2 + (map_width - center_x));
    int rect_h = center_y + vp_height/2 < map_height ? vp_height : (vp_height/2 + (map_height - center_y));
    // construct rectangle objects
    SDL_Rect dst = {
        dst_x*grid_spacing,
        dst_y*grid_spacing,
        rect_w*grid_spacing,
        rect_h*grid_spacing
    };
    SDL_Rect src = {
        src_x*grid_spacing,
        src_y*grid_spacing,
        rect_w*grid_spacing,
        rect_h*grid_spacing
    };
    // render to windo
    SDL_RenderCopy(renderer, bg_texture, &src, &dst); 
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
        // draw sprite if exists
        if (is_occupied(sprite(x,y))) {
            SDL_RenderCopyEx(
                    renderer, 
                    sprite(x,y)->get_texture(), 
                    sprite(x,y)->get_srcrect(), 
                    sprite(x,y)->get_dstrect(center_x-vp_width/2, center_y-vp_height/2),
                    sprite(x,y)->get_angle(),
                    NULL,
                    sprite(x,y)->get_flip()
                    );
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

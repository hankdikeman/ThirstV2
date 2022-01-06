/*
 * descr: header file for Tilemap container class
 * author: Henry Dikeman
 */

// stdlib headers
#include <stdbool.h>
#include <iostream>

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
        Sprite*& sprite(int x, int y) { return map[x*map_width + y].sprite_layer; }
        Static*& statics(int x, int y) { return map[x*map_width + y].static_layer; }
        Static*& background(int x, int y) { return map[x*map_width + y].background_layer; }

        // map getters
        int get_height() const { return map_height; }
        int get_width() const { return map_width; }
        int get_spacing() const { return grid_spacing; }

        // entity shift methods
        bool sprite_dec_x(int x, int y);
        bool sprite_inc_x(int x, int y);
        bool sprite_dec_y(int x, int y);
        bool sprite_inc_y(int x, int y);

        // status methods
        bool is_occupied(int x, int y) const;
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

// decrement x coordinate of sprite at (x,y)
bool Tilemap::sprite_dec_x(int x, int y) {
    // test whether target is in bounds
    if (x != 0) {
        // test whether requested position contains sprite
        if (is_occupied(x, y)) {
            // test whether target position is empty
            if (!is_occupied(x-1, y)) {
                // retrieve pointer
                Sprite* moved_sprite = this->sprite(x, y);
                // move sprite to new position
                this->sprite(x-1, y) = moved_sprite;
                // remove from old position
                this->sprite(x, y) = 0;
                // adjust position
                moved_sprite->add_xpos(-grid_spacing);
                // return success
                return true;
            }
        }
    }
    // return failure
    return false;
}

// increment x coordinate of sprite at (x,y)
bool Tilemap::sprite_inc_x(int x, int y) {
    // test whether target is in bounds
    if (x != map_width-1) {
        // test whether requested position contains sprite
        if (is_occupied(x, y)) {
            // test whether target position is empty
            if (!is_occupied(x+1, y)) {
                // retrieve pointer
                Sprite* moved_sprite = this->sprite(x, y);
                // move sprite to new position
                this->sprite(x+1, y) = moved_sprite;
                // remove from old position
                this->sprite(x, y) = 0;
                // adjust position
                moved_sprite->add_xpos(grid_spacing);
                // return success
                return true;
            }
        }
    }
    // return failure
    return false;
}

// decrement y coordinate of sprite at (x,y)
bool Tilemap::sprite_dec_y(int x, int y) {
    // test whether target is in bounds
    if (y != 0) {
        // test whether requested position contains sprite
        if (is_occupied(x, y)) {
            // test whether target position is empty
            if (!is_occupied(x, y-1)) {
                // retrieve pointer
                Sprite* moved_sprite = this->sprite(x, y);
                // move sprite to new position
                this->sprite(x, y-1) = moved_sprite;
                // remove from old position
                this->sprite(x, y) = 0;
                // adjust position
                moved_sprite->add_ypos(-grid_spacing);
                // return success
                return true;
            }
        }
    }
    // return failure
    return false;
}

// increment y coordinate of sprite at (x,y)
bool Tilemap::sprite_inc_y(int x, int y) {
    // test whether target is in bounds
    if (y != map_height-1) {
        // test whether requested position contains sprite
        if (is_occupied(x, y)) {
            // test whether target position is empty
            if (!is_occupied(x, y+1)) {
                // retrieve pointer
                Sprite* moved_sprite = this->sprite(x, y);
                // move sprite to new position
                this->sprite(x, y+1) = moved_sprite;
                // remove from old position
                this->sprite(x, y) = 0;
                // adjust position
                moved_sprite->add_ypos(grid_spacing);
                // return success
                return true;
            }
        }
    }
    // return failure
    return false;
}

// test whether given location is occupied
bool Tilemap::is_occupied(int x, int y) const {
    return map[x*map_width + y].sprite_layer != 0;
}

#endif

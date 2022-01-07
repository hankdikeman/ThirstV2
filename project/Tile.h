/*
 * descr: header file for Tile struct container
 * author: Henry Dikeman
 */

// standardlib headers
#include <iostream>

// internlib headers
#include "Static.h"
#include "Sprite.h"

#ifndef TILE_H
#define TILE_H

struct Tile {
    // default constructor
    Tile() : 
        sprite_layer(0), 
        static_layer(0), 
        background_layer(0) {}
    // default destructor
    ~Tile() {
        if (sprite_layer) {
            // show deleted pointer
            std::cout << "free Sprite sprite: ";
            std::cout << sprite_layer << std::endl;
            delete sprite_layer;
        }
        if (static_layer) {
            // show deleted pointer
            std::cout << "free Static static: ";
            std::cout << static_layer << std::endl;
            delete static_layer;
        }
        if (background_layer) {
            // show deleted pointer
            std::cout << "free Static bg: ";
            std::cout << background_layer << std::endl;
            delete background_layer;
        }
    }

    // pointer variables
    Sprite* sprite_layer;
    Static* static_layer;
    Static* background_layer;
};

#endif

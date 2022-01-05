/*
 * descr: header file for Tile struct container
 * author: Henry Dikeman
 */

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
        if (sprite_layer) delete sprite_layer;
        if (static_layer) delete static_layer;
        if (background_layer) delete background_layer;
    }
    Sprite* sprite_layer;
    Static* static_layer;
    Static* background_layer;
};

#endif

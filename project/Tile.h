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
        movement_layer(0), 
        static_layer(0), 
        background_layer(0) {}
    // default destructor
    ~Tile() {
        if (movement_layer) delete movement_layer;
        if (static_layer) delete static_layer;
        if (background_layer) delete background_layer;
    }
    Sprite* movement_layer;
    Drawable* static_layer;
    Static* background_layer;
};

#endif

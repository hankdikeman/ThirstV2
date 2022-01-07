/*
 * descr: header file for Tile struct container
 * author: Henry Dikeman
 */

// standardlib headers
#include <iostream>
#include <memory>

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
    ~Tile() {}

    // pointer variables (static and bg layers should be made unique if not used in lists later)
    std::shared_ptr<Sprite> sprite_layer;
    std::shared_ptr<Static> static_layer;
    std::shared_ptr<Static> background_layer;
};

#endif

/*
 * descr: header file for Tilemap container class
 * author: Henry Dikeman
 */

// internlib headers
#include "Static.h"
#include "Sprite.h"
#include "Tile.h"

#ifndef TILEMAP_H
#define TILEMAP_H

class Tilemap {
    private:
        int map_height, map_width;
        Tile* map;
    public:
        // constructors
        Tilemap();
        Tilemap(int width, int height);
        // destructor
        ~Tilemap();
        // get methods
        Tile get(int x, int y);
};

// default constructor with default size and width
Tilemap::Tilemap() : 
    map_height(64), 
    map_width(64) {
        // allocate map array
        map = new Tile[map_height * map_width];
    }

// constructor with parametrized width and height
Tilemap::Tilemap(int width, int height) : 
    map_height(height), 
    map_width(width) {
        // allocate map array
        map = new Tile[map_height * map_width];
    }

// destructor
Tilemap::~Tilemap() {
    // deallocate map array
    delete[] map;
}

// return reference to tile at (x,y)
Tile& Tilemap::get(int x, int y) {
    return map[x*map_width + y];
}

#endif

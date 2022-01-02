/*
 * descr: header file for Static entity class
 * author: Henry Dikeman
 */

// stdlib headers
#include <vector>

// externlib headers
#include <SDL.h>

// internlib headers
#include "Drawable.h"

#ifndef STATIC_H
#define STATIC_H

class Static: public Drawable {
    public:
        // constructors
        Static(std::vector<int> pos, std::vector<int> size, SDL_Texture* text);
        Static(std::vector<float> pos, std::vector<int> size, SDL_Texture* text);
};

// int constructor
Static::Static(std::vector<int> pos, std::vector<int> size, SDL_Texture* text) : 
    Drawable(pos, size, text) {}

// float constructor
Static::Static(std::vector<float> pos, std::vector<int> size, SDL_Texture* text) : 
    Drawable(pos, size, text) {}

#endif

/*
 * descr: header file for Static entity class. Animations which do not have cycles
 * author: Henry Dikeman
 */

// stdlib headers
#include <array>

// externlib headers
#include <SDL.h>

// internlib headers
#include "Drawable.h"

#ifndef STATIC_H
#define STATIC_H

class Static: public Drawable {
    public:
        // constructors
        Static(std::array<int,2> pos, std::array<int,2> size, SDL_Texture* text);
        // implemented virtual method
        virtual const SDL_Rect* get_srcrect();
};

// int constructor
Static::Static(std::array<int,2> pos, std::array<int,2> size, SDL_Texture* text) : 
    Drawable(pos, size, text) {}

// provide src rectangle for renderer
const SDL_Rect* Static::get_srcrect() {
    // update source rectangle from position data
    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = drawsize[0];
    srcrect.h = drawsize[1];
    // return rectangle
    return &srcrect;
}

#endif

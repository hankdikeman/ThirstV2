/*
 * descr: header file for Static entity class. Animations which do not have cycles
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

// provide src rectangle for renderer
SDL_Rect Sprite::get_srcrect() {
    // update destination rectangle from position data
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = w;
    dstrect.h = h;
    // return rectangle
    return dstrect;
}

#endif

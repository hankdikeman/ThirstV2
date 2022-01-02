/*
 * descr: header file for Sprite entity class
 * author: Henry Dikeman
 */

// stdlib headers
#include <vector>

// externlib headers
#include <SDL.h>

// internlib headers
#include "Drawable.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite: public Drawable {
    public:
        // constructors
        Sprite(std::vector<int> pos, std::vector<int> size, SDL_Texture* text);
        Sprite(std::vector<float> pos, std::vector<int> size, SDL_Texture* text);
};

// int constructor
Sprite::Sprite(std::vector<int> pos, std::vector<int> size, SDL_Texture* text) : 
    Drawable(pos, size, text) {}

// float constructor
Sprite::Sprite(std::vector<float> pos, std::vector<int> size, SDL_Texture* text) : 
    Drawable(pos, size, text) {}

#endif

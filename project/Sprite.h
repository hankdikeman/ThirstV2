/*
 * descr: header file for Sprite entity class. Animations which have repeated cycles
 * author: Henry Dikeman
 */

// stdlib headers
#include <array>

// externlib headers
#include <SDL.h>

// internlib headers
#include "Drawable.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite: public Drawable {
    protected:
        int num_cycles;
        int curr_cycle;
    public:
        // constructors
        Sprite(std::array<int, 2> pos, std::array<int, 2> size, SDL_Texture* text);
        // destructors
        virtual ~Sprite();
        // implemented virtual method
        virtual const SDL_Rect* get_srcrect();
};

// int constructor
Sprite::Sprite(std::array<int, 2> pos, std::array<int, 2> size, SDL_Texture* text) : 
    Drawable(pos, size, text)
    {
        // get dimensions of spritesheet
        int spritesheet_w, spritesheet_h;
        SDL_QueryTexture(texture, NULL, NULL, &spritesheet_w, &spritesheet_h);
        // set number of cycles with spritesheet width and width
        num_cycles = spritesheet_w / drawsize[0];

        // set current cycle to 0
        curr_cycle = 0;
    }

// destructor
Sprite::~Sprite() {}

// provide src rectangle for renderer
const SDL_Rect* Sprite::get_srcrect() {
    // update source rectangle from position data
    srcrect.x = curr_cycle*drawsize[0];
    srcrect.y = 0;
    srcrect.w = drawsize[0];
    srcrect.h = drawsize[1];
    // update cycle number
    curr_cycle = (curr_cycle+1) % num_cycles;
    // return rectangle
    return &srcrect;
}

#endif

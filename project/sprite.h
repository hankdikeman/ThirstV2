/*
 * descr: header file for Sprite entity class. Animations which have repeated cycles
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
    protected:
        int num_cycles;
        int curr_cycle;
    public:
        // constructors
        Sprite(std::vector<int> pos, std::vector<int> size, SDL_Texture* text);
        Sprite(std::vector<float> pos, std::vector<int> size, SDL_Texture* text);
        // implemented virtual method
        virtual SDL_Rect get_srcrect();
};

// int constructor
Sprite::Sprite(std::vector<int> pos, std::vector<int> size, SDL_Texture* text) : 
    curr_cycle(0) ,
    Drawable(pos, size, text)
    {
        // get dimensions of spritesheet
        int spritesheet_w, spritesheet_h;
        SDL_QueryTexture(texture, NULL, NULL, &spritesheet_w, &spritesheet_h);
        // set number of cycles with spritesheet width and width
        num_cycles = spritesheet_w / w;
    }

// float constructor
Sprite::Sprite(std::vector<float> pos, std::vector<int> size, SDL_Texture* text) : 
    curr_cycle(0) ,
    Drawable(pos, size, text)
    {
        // get dimensions of spritesheet
        int spritesheet_w, spritesheet_h;
        SDL_QueryTexture(texture, NULL, NULL, &spritesheet_w, &spritesheet_h);
        // set number of cycles with spritesheet width and width
        num_cycles = spritesheet_w / w;
    }

// provide src rectangle for renderer
SDL_Rect Sprite::get_srcrect() {
    // update destination rectangle from position data
    dstrect.x = curr_cycle*w;
    dstrect.y = 0;
    dstrect.w = w;
    dstrect.h = h;
    // update cycle number
    curr_cycle = (curr_cycle+1) % num_cycles;
    // return rectangle
    return dstrect;
}

#endif

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
        std::array<int, 2> srcsize;
        int num_cycles;
        int curr_frame;
    public:
        // constructors
        Sprite(std::array<int, 2> pos, std::array<int, 2> dsize, std::array<int, 2> ssize, SDL_Texture* text);
        Sprite(std::array<int, 2> pos, std::array<int, 2> dsize, int n_cyc, SDL_Texture* text);
        // destructors
        virtual ~Sprite();
        // implemented virtual method
        virtual const SDL_Rect* get_srcrect();
        // animation cycle iteration
        void increment_frame();
};

// source size constructor
Sprite::Sprite(std::array<int, 2> pos, std::array<int, 2> dsize, std::array<int, 2> ssize, SDL_Texture* text) :
    Drawable(pos, dsize, text),
    srcsize(ssize) {
        // get dimensions of spritesheet
        int spritesheet_w, spritesheet_h;
        SDL_QueryTexture(texture, NULL, NULL, &spritesheet_w, &spritesheet_h);
        // set number of cycles with spritesheet width and width
        num_cycles = spritesheet_w / srcsize[0];
        // set current cycle to 0
        curr_frame = 0;
}

// cycle specified constructor
Sprite::Sprite(std::array<int, 2> pos, std::array<int, 2> dsize, int n_cyc, SDL_Texture* text) :
    Drawable(pos, dsize, text),
    num_cycles(n_cyc) {
        // get dimensions of spritesheet
        int spritesheet_w, spritesheet_h;
        SDL_QueryTexture(texture, NULL, NULL, &spritesheet_w, &spritesheet_h);
        // set number of cycles with spritesheet width and width
        srcsize[0] = spritesheet_w / num_cycles;
        srcsize[1] = spritesheet_h;
        // set current cycle to 0
        curr_frame = 0;
}

// destructor
Sprite::~Sprite() {}

// provide src rectangle for renderer
const SDL_Rect* Sprite::get_srcrect() {
    // update source rectangle from position data
    srcrect.x = curr_frame*srcsize[0];
    srcrect.y = 0;
    srcrect.w = srcsize[0];
    srcrect.h = srcsize[1];
    // return rectangle
    return &srcrect;
}

void Sprite::increment_frame() {
    curr_frame = (curr_frame + 1) % num_cycles;
}

#endif

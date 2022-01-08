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
        int curr_frame;
    public:
        // include superclass setter for overloading
        using Drawable::set_texture;

        // constructors
        Sprite() {}

        // destructors
        virtual ~Sprite() {}

        // overloaded texture setters
        void set_texture(SDL_Texture* text, int num_cycles);
        void set_texture(SDL_Texture* text, std::array<int, 2> ssize);

        // implemented virtual method
        virtual const SDL_Rect* get_srcrect();

        // animation cycle iteration
        void increment_frame();
};

// source size texture setter
void Sprite::set_texture(SDL_Texture* text, std::array<int, 2> srcsize) {
    // set texture and source size array
    this->set_texture(text);
    this->set_srcsize(srcsize);
    // get dimensions of spritesheet
    int spritesheet_w, spritesheet_h;
    SDL_QueryTexture(texture, NULL, NULL, &spritesheet_w, &spritesheet_h);
    // set number of cycles with spritesheet width and width
    this->num_cycles = spritesheet_w / srcsize[0];
}

// cycle specified texture setter
void Sprite::set_texture(SDL_Texture* text, int num_cycles) {
    // set texture and number of cycles
    this->set_texture(text);
    this->num_cycles = num_cycles;
    // get dimensions of spritesheet
    int spritesheet_w, spritesheet_h;
    SDL_QueryTexture(texture, NULL, NULL, &spritesheet_w, &spritesheet_h);
    // set number of cycles with spritesheet width and width
    std::array<int, 2> ssize = {spritesheet_w / num_cycles, spritesheet_h};
    this->set_srcsize(ssize);
}

// provide src rectangle for renderer
const SDL_Rect* Sprite::get_srcrect() {
    // update source rectangle from position data
    srcrect.x = curr_frame * srcsize[0];
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

/*
 * descr: Sprite class definition for animated entity objects. Inherits Drawable
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

// define direction enum
enum class SpriteDirection { 
    RIGHT, 
    LEFT, 
    UP, 
    DOWN 
};

// define sprite states
enum class SpriteState { 
    PLAYER, 
    IDLING, 
    ATTACKING, 
    FLEEING
};

class Sprite: public Drawable {
    private:
        // animation info
        int num_cycles;
        int curr_frame;
        int sprite_health;
        int sprite_max_health;
        // state info
        SpriteDirection sprite_direction; 
        SpriteState sprite_state;
    public:
        // constructors
        Sprite() {}

        // destructors
        virtual ~Sprite() {}

        // include superclass setter for overloading
        using Drawable::set_texture;
        // overloaded texture setters
        void set_texture(SDL_Texture* text, int num_cycles);
        void set_texture(SDL_Texture* text, std::array<int, 2> ssize);

        // direction reference getter
        SpriteDirection& direction() { return sprite_direction; }
        // state setter and getter
        SpriteState& state() { return sprite_state; }

        // health reference getters
        int& max_health() { return sprite_max_health; }
        int& health() { return sprite_health; }


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
    this->num_cycles = spritesheet_w / this->src_w();
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
    srcrect.x = curr_frame * this->src_w();
    srcrect.y = 0;
    srcrect.w = this->src_w();
    srcrect.h = this->src_h();
    // return rectangle
    return &srcrect;
}

void Sprite::increment_frame() {
    curr_frame = (curr_frame + 1) % num_cycles;
}

#endif

/*
 * descr: abstract baseclass definition for drawable objects
 * author: Henry Dikeman
 */

// stdlib headers
#include <iostream>
#include <array>
#include <bitset>
#include <stdbool.h>

// externlib headers
#include <SDL.h>

#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable {
    protected:
        std::array<int, 2> srcsize;
        std::array<int, 2> position;
        std::array<int, 2> drawsize;
        uint8_t sprite_id;
        SDL_Texture * texture;
        SDL_Rect dstrect;
        SDL_Rect srcrect;
    public:
        // constructors
        Drawable() {}

        // position reference getters
        int& x() { return position[0]; }
        int& y() { return position[1]; }
        void set_position(const std::array<int, 2>& pos) { position[0] = pos[0]; position[1] = pos[1]; }
        // drawsize reference getters
        int& w() { return drawsize[0]; }
        int& h() { return drawsize[1]; }
        void set_drawsize(const std::array<int, 2>& size) { drawsize[0] = size[0]; drawsize[1] = size[1]; }
        // srcsize reference getters
        int& src_w() { return srcsize[0]; }
        int& src_h() { return srcsize[1]; }
        void set_srcsize(const std::array<int, 2>& size) { srcsize[0] = size[0]; srcsize[1] = size[1]; }
        // id reference getter
        uint8_t& id() { return sprite_id; }

        // texture setter and getter
        SDL_Texture* get_texture() { return texture; }
        void set_texture(SDL_Texture* text) { this->texture = text; }

        // source and destination rectangle methods
        virtual const SDL_Rect* get_srcrect() = 0;
        const SDL_Rect* get_dstrect(int offset_x = 0, int offset_y = 0);
};

// provide dest rectangle for renderer
const SDL_Rect* Drawable::get_dstrect(int offset_x, int offset_y) {
    // update destination rectangle from position data
    dstrect.x = (this->x()-offset_x) * this->w();
    dstrect.y = (this->y()-offset_y) * this->h();
    dstrect.w = this->w();
    dstrect.h = this->h();
    // return rectangle
    return &dstrect;
}

#endif

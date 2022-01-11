/*
 * descr: header file for Drawable abstract class
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
        uint8_t id;
        SDL_Texture * texture;
        SDL_Rect dstrect;
        SDL_Rect srcrect;
    public:
        // constructors
        Drawable() {}

        // getters
        int get_x() const { return position[0]; }
        int get_y() const { return position[1]; }
        int get_w() const { return drawsize[0]; }
        int get_h() const { return drawsize[1]; }
        SDL_Texture* get_texture() { return texture; }
        uint8_t get_id() { return id; }

        // position setters
        void set_x(int xpos) { position[0] = xpos; }
        void add_x(int xpos) { position[0] += xpos; }
        void set_y(int ypos) { position[1] = ypos; }
        void add_y(int ypos) { position[1] += ypos; }
        void set_position(const std::array<int, 2>& pos) { position[0] = pos[0]; position[1] = pos[1]; }
        // drawsize setters
        void set_draw_w(int w) { drawsize[0] = w; }
        void set_draw_h(int h) { drawsize[1] = h; }
        void set_drawsize(const std::array<int, 2>& size) { drawsize[0] = size[0]; drawsize[1] = size[1]; }
        // srcsize setter
        void set_srcsize(const std::array<int, 2>& size) { srcsize[0] = size[0]; srcsize[1] = size[1]; }
        // texture setter
        void set_texture(SDL_Texture* text) { texture = text; }
        // id setter
        void set_id(uint8_t id) { this->id = id; }

        // source and destination rectangle methods
        virtual const SDL_Rect* get_srcrect() = 0;
        const SDL_Rect* get_dstrect();
};

// provide dest rectangle for renderer
const SDL_Rect* Drawable::get_dstrect() {
    // update destination rectangle from position data
    dstrect.x = get_x() * get_w();
    dstrect.y = get_y() * get_h();
    dstrect.w = get_w();
    dstrect.h = get_h();
    // return rectangle
    return &dstrect;
}

#endif

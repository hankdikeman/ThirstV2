/*
 * descr: header file for Drawable abstract class
 * author: Henry Dikeman
 */

// stdlib headers
#include <iostream>
#include <array>
#include <stdbool.h>

// externlib headers
#include <SDL.h>

#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable {
    protected:
        std::array<int, 2> position;
        std::array<int, 2> drawsize;
        SDL_Texture * texture;
        SDL_Rect dstrect;
        SDL_Rect srcrect;
    public:
        // constructors
        Drawable(std::array<int, 2> pos, std::array<int, 2> size, SDL_Texture* text);

        // getters
        int get_xpos() const { return position[0]; }
        int get_ypos() const { return position[1]; }
        int get_width() const { return drawsize[0]; }
        int get_height() const { return drawsize[1]; }
        SDL_Texture* get_texture() { return texture; }

        // position setters
        void set_xpos(int xpos) { position[0] = xpos; }
        void set_ypos(int ypos) { position[1] = ypos; }
        void add_xpos(int xpos) {
            // std::cout << std::endl << "x: " << position[0] << "->"; 
            position[0] += xpos; 
            // std::cout << position[0] << std::endl; 
        }
        void add_ypos(int ypos) {
            // std::cout << std::endl << "y: " << position[1] << "->"; 
            position[1] += ypos; 
            // std::cout << position[1] << std::endl;
        }
        void set_pos(const std::array<int, 2> &pos) { position[0] = pos[0]; position[1] = pos[1]; }
        // size setters
        void set_width(int w) { drawsize[0] = w; }
        void set_height(int h) { drawsize[1] = h; }
        void set_size(const std::array<int, 2> &size) { drawsize[0] = size[0]; drawsize[1] = size[1]; }
        // texture setter
        void set_texture(SDL_Texture* text) { texture = text; }

        // source and destination rectangle methods
        virtual const SDL_Rect* get_srcrect() = 0;
        const SDL_Rect* get_dstrect();
};

// float constructor
Drawable::Drawable(std::array<int, 2> pos, std::array<int, 2> size, SDL_Texture* text) :
    position(pos),
    drawsize(size),
    texture(text) {}

// provide dest rectangle for renderer
const SDL_Rect* Drawable::get_dstrect() {
    // update destination rectangle from position data
    dstrect.x = position[0]*drawsize[0];
    dstrect.y = position[1]*drawsize[1];
    dstrect.w = drawsize[0];
    dstrect.h = drawsize[1];
    // return rectangle
    return &dstrect;
}

#endif

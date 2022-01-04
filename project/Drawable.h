/*
 * descr: header file for Drawable abstract class
 * author: Henry Dikeman
 */

// stdlib headers
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
        int get_xpos() { return (int) position[0]; }
        int get_ypos() { return (int) position[1]; }
        int get_width() { return drawsize[0]; }
        int get_height() { return drawsize[1]; }
        SDL_Texture* get_texture() { return texture; }

        // position setters
        void set_xpos(int xpos) { position[0] = xpos; }
        void set_ypos(int ypos) { position[1] = ypos; }
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

        // abstract method to provide source rectangle
        bool collision(Drawable &draw);
        bool collision(const std::array<int, 2> &pos, const std::array<int, 2> &size);
        
};

// float constructor
Drawable::Drawable(std::array<int, 2> pos, std::array<int, 2> size, SDL_Texture* text) :
    position(pos),
    drawsize(size),
    texture(text) {}

// provide dest rectangle for renderer
const SDL_Rect* Drawable::get_dstrect() {
    // update destination rectangle from position data
    dstrect.x = position[0];
    dstrect.y = position[1];
    dstrect.w = drawsize[0];
    dstrect.h = drawsize[1];
    // return rectangle
    return &dstrect;
}

// test whether two objects are currently colliding
bool Drawable::collision(Drawable &draw) {
    // test overlap in x direction
    int l1_x = position[0];
    int r1_x = l1_x + drawsize[0];
    int l2_x = draw.get_xpos();
    int r2_x = r1_x + draw.get_width();
    // if no overlap in x, return false
    if (l1_x > r2_x  || l2_x > r1_x) { return false; }
    // test overlap in y direction
    int l1_y = position[1];
    int r1_y = l1_y + drawsize[1];
    int l2_y = draw.get_ypos();
    int r2_y = r1_y + draw.get_height();
    // if no overlap in y, return false
    if (r1_y > l2_y  || r2_y > l1_y) { return false; }
    // default true for overlap
    return true;
}

// test whether two objects are currently colliding
bool Drawable::collision(const std::array<int, 2> &pos, const std::array<int, 2> &size) {
    // test overlap in x direction
    int l1_x = position[0];
    int r1_x = l1_x + drawsize[0];
    int l2_x = pos[0];
    int r2_x = r1_x + size[0];
    // if no overlap in x, return false
    if (l1_x > r2_x  || l2_x > r1_x) { return false; }
    // test overlap in y direction
    int l1_y = position[1];
    int r1_y = l1_y + drawsize[1];
    int l2_y = pos[1];
    int r2_y = r1_y + size[1];
    // if no overlap in y, return false
    if (r1_y > l2_y  || r2_y > l1_y) { return false; }
    // default true for overlap
    return true;
}

#endif

/*
 * descr: header file for Drawable abstract class
 * author: Henry Dikeman
 */

// stdlib headers
#include <vector>

// externlib headers
#include <SDL.h>

#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable {
    protected:
        float x, y;
        int w, h;
        SDL_Texture * texture;
        SDL_Rect dstrect;
        SDL_Rect srcrect;
    public:
        // constructors
        Drawable(std::vector<float> pos, std::vector<int> size, SDL_Texture* text);
        Drawable(std::vector<int> pos, std::vector<int> size, SDL_Texture* text);

        // getters
        int get_xpos() { return (int) x; }
        int get_ypos() { return (int) y; }
        int get_width() { return w; }
        int get_height() { return h; }
        SDL_Texture* get_texture() { return texture; }

        // position setters
        void set_xpos(float xpos) { x = xpos; }
        void set_xpos(int xpos) { x = (float) xpos; }
        void set_ypos(float ypos) { y = ypos; }
        void set_ypos(int ypos) { y = (float) ypos; }
        void set_pos(std::vector<int> pos) { x = (float) pos[0]; y = (float) pos[1]; }
        void set_pos(std::vector<float> pos) {x = pos[0]; y = pos[1]; }
        // size setters
        void set_width(int wval) { w = wval; }
        void set_height(int hval) { h = hval; }
        void set_size(std::vector<int> size) { h = size[0]; w = size[1]; }
        // texture setter
        void set_texture(SDL_Texture* text) { texture = text; }

        // abstract method to provide source rectangle
        virtual SDL_Rect get_srcrect() = 0; 
        // implemented method to provide dest rectangle
        SDL_Rect get_dstrect();
        
};

// int constructor
Drawable::Drawable(std::vector<int> pos, std::vector<int> size, SDL_Texture* text) :
    x((float) pos[0]),
    y((float) pos[1]),
    w(size[0]),
    h(size[1]),
    texture(text) {}

// float constructor
Drawable::Drawable(std::vector<float> pos, std::vector<int> size, SDL_Texture* text) :
    x(pos[0]),
    y(pos[1]),
    w(size[0]),
    h(size[1]),
    texture(text) {}

// provide dest rectangle for renderer
SDL_Rect Drawable::get_dstrect() {
    // update destination rectangle from position data
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = w;
    dstrect.h = h;
    // return rectangle
    return dstrect;
}

#endif

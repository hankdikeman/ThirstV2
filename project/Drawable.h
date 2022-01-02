/*
 * descr: header file for drawable abstract class
 * author: Henry Dikeman
 */

#include <SDL.h>

#ifndef DATE_H
#define DATE_H

class Drawable {
    private:
        float x, y;
        int w, h;
        SDL_Texture * texture;
        SDL_Rect dstrect;
        SDL_Rect srcrect;
    public:
        Drawable(int xpos, int ypos, int wval, int hval, SDL_Texture* text) {
            // set positions
            x = (float) xpos;
            y = (float) ypos;
            // set dimensions
            w = wval;
            h = hval;
            // save ptr to texture
            texture = text;
        }

        // position getters
        int get_xpos() { return (int) x; }
        int get_ypos() { return (int) y; }
        int get_width() { return w; }
        int get_height() { return h; }
        SDL_Texture* get_texture() { return texture; }

        // abstract method to provide source rectangle
        virtual SDL_Rect get_srcrect() = 0; 
        SDL_Rect get_dstrect();
        
};

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

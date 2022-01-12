/*
 * descr: Static class definition for non-animated entity objects. Inherits Drawable
 * author: Henry Dikeman
 */

// stdlib headers
#include <array>

// externlib headers
#include <SDL.h>

// internlib headers
#include "Drawable.h"

#ifndef STATIC_H
#define STATIC_H

class Static: public Drawable {
    public:
        // include superclass setter for overloading
        using Drawable::set_texture;

        // constructors
        Static() {}

        // destructors
        virtual ~Static() {}

        // implemented virtual method
        virtual const SDL_Rect* get_srcrect();
};

// provide src rectangle for renderer
const SDL_Rect* Static::get_srcrect() {
    // update source rectangle from position data
    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = this->src_w();
    srcrect.h = this->src_h();
    // return rectangle
    return &srcrect;
}

#endif

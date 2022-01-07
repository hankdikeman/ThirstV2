/*
 * descr: header file for Sprite entity class. Animations which have repeated cycles
 * author: Henry Dikeman
 */

// stdlib headers
#include <iostream>
#include <array>
#include <vector>

// externlib headers
#include <SDL.h>

// internlib headers
#include "Drawable.h"
#include "Sprite.h"

#ifndef ENTITYLIST_H
#define ENTITYLIST_H

class EntityList {
    private:
        vector<Sprite> e_list;

};

#endif

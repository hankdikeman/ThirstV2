/*
 * descr: texture and sound manager classes
 * author: Henry Dikeman
 */

// stdlib headers
#include <iostream>
#include <bitset>
#include <memory>
#include <array>
#include <stdbool.h>

// externlib headers
#include <SDL.h>

// internlib headers
#include "Sprite.h"

#ifndef ASSETMANAGERS_H
#define ASSETMANAGERS_H

class TextureManager {
    private:
        // hashmap for textures
    public:
        // constructor
        TextureManager() {}

        // texture loader
        void init_textures();

        // index texture from id
        SDL_Texture* query_texture(std::bitset<8> id);

        // clean up loaded textures
        void clean_up();
};

class SoundManager {
    private:
        // hashmap for textures
    public:
        // constructor
        SoundManager() {}

        // sound loader
        void init_sounds();

        // index sound from id
        Mix_Chunk* query_sound(std::bitset<8> id);

        // clean up loaded textures
        void clean_up();
};

#endif

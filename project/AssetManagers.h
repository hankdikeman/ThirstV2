/*
 * descr: texture and sound manager classes
 * author: Henry Dikeman
 */

// stdlib headers
#include <iostream>
#include <map>
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
        std::unordered_map<std::bitset<8>, SDL_Texture*> texture_map;
    public:
        // constructor
        TextureManager() {}

        // texture loader
        void init_textures();

        // index texture from id
        SDL_Texture*& query_texture(std::bitset<8> id) { return texture_map[id]; }

        // clean up loaded textures
        void clean_up();
};

class SoundManager {
    private:
        std::unordered_map<std::bitset<8>, Mix_Chunk*> sound_map;
    public:
        // constructor
        SoundManager() {}

        // sound loader
        void init_sounds();

        // index sound from id
        Mix_Chunk*& query_sound(std::bitset<8> id) { return sound_map[id]; }

        // clean up loaded textures
        void clean_up();
};

#endif

/*
 * descr: texture and sound manager classes
 * author: Henry Dikeman
 */

// stdlib headers
#include <iostream>
#include <unordered_map>
#include <memory>
#include <array>
#include <stdbool.h>

// externlib headers
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

// internlib headers
#include "Entities.h"

#ifndef ASSETMANAGERS_H
#define ASSETMANAGERS_H

class TextureManager {
    private:
        std::unordered_map<uint8_t, SDL_Texture*> texture_map;
        int grid_size;
    public:
        // constructor
        TextureManager(int grid_size) : grid_size(grid_size) {}

        // destructor
        ~TextureManager();

        // setters and getters for grid
        int get_grid_size() { return grid_size; }
        void set_grid_size(int grid_size) { this->grid_size = grid_size; }

        // texture loader
        void init_textures(SDL_Renderer*& renderer);

        // index texture from id
        SDL_Texture*& query_texture(uint8_t id) { return texture_map[id]; }
};

void TextureManager::init_textures(SDL_Renderer*& renderer) {
    // *** EVENTUALLY READ IN XML FILE FOR TEXTURE TRACKING *** //
    
    // initialize ID
    uint8_t newID = (0b00000001);
    // load surface
    SDL_Surface* newSurf = IMG_Load("Resources/PCSprite.png");
    // convert to texture
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, newSurf);
    // free surface
    SDL_FreeSurface(newSurf);
    // push to hashmap
    texture_map[newID] = newTexture;
}

TextureManager::~TextureManager() {
    // clean up retained resources in hashmap
    for (std::pair<uint8_t, SDL_Texture*> tpair : texture_map) {
        SDL_DestroyTexture(tpair.second);
    }
}

class SoundManager {
    private:
        std::unordered_map<uint8_t, Mix_Chunk*> sound_map;
    public:
        // constructor
        SoundManager() {}

        // destructor
        ~SoundManager();

        // sound loader
        void init_sounds();

        // index sound from id
        Mix_Chunk*& query_sound(uint8_t id) { return sound_map[id]; }
};

void SoundManager::init_sounds() {
    // *** EVENTUALLY READ IN XML FILE FOR SOUND TRACKING *** //
    
    // initialize sound and ID
    uint8_t newID = (0b00000001);
    Mix_Chunk* newSound = Mix_LoadWAV("playerAttack.wav");
    // push to hashmap
    sound_map[newID] = newSound;
}

SoundManager::~SoundManager() {
    // clean up retained resources in hashmap
    for (std::pair<uint8_t, Mix_Chunk*> spair : sound_map) {
        Mix_FreeChunk(spair.second);
    }
}

#endif

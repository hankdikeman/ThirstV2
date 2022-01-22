/*
 * descr: texture and sound manager classes
 * author: Henry Dikeman
 */

// stdlib headers
#include <iostream>
#include <unordered_map>
#include <memory>
#include <array>
#include <string>
#include <stdbool.h>

// externlib headers
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <pugixml.hpp>

// internlib headers
#include "Sprite.h"
#include "Static.h"

#ifndef ASSETMANAGERS_H
#define ASSETMANAGERS_H

class TextureManager {
    private:
        SDL_Renderer* renderer;
        std::unordered_map<uint8_t, SDL_Texture*> texture_map;
        int grid_size;
    public:
        // constructor
        TextureManager(SDL_Renderer* renderer, int grid_size) : renderer(renderer), grid_size(grid_size) {}

        // destructor
        ~TextureManager();

        // setters and getters for grid
        int get_grid_size() { return grid_size; }
        void set_grid_size(int grid_size) { this->grid_size = grid_size; }

        // texture loader
        void init_textures();

        // index texture from id
        SDL_Texture*& query_texture(uint8_t id);
};

SDL_Texture*& TextureManager::query_texture(uint8_t id) { 
    return texture_map[id]; 
}

void TextureManager::init_textures() {
    
    // load in texture xml data from file
    pugi::xml_document text_doc;
    if(!text_doc.load_file("Resources/TextureDirectory.xml")) {
        std::cout << "TextDir not loaded right" << std::endl;
    }
    pugi::xml_node text_directory = text_doc.child("TextureDirectory");

    // loop through texture XML data
    for (pugi::xml_node record = text_directory.first_child(); record; record = record.next_sibling()) {
        // load ID
        uint8_t newID = record.attribute("id").as_int();
        
        // generate surface from image
        SDL_Surface* newSurf = IMG_Load(record.child_value("filename"));
        // convert to texture
        SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, newSurf);

        if (newSurf == nullptr) {
            std::cout << "failed to load image!" << std::endl;
        }

        // free surface
        SDL_FreeSurface(newSurf);
        // push to hashmap
        texture_map[newID] = newTexture;

        // log ID and filename
        std::cout << "Text ID: " << unsigned(newID);
        std::cout << ", ptr Address: " << texture_map[newID];
        std::cout << ", Filename: " << record.child_value("filename") << std::endl;
    }
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
    // load in sound xml data from file
    pugi::xml_document sound_doc;
    if(!sound_doc.load_file("Resources/SoundDirectory.xml")) {
        std::cout << "SoundDir not loaded right" << std::endl;
    }
    pugi::xml_node sound_directory = sound_doc.child("SoundDirectory.xml");

    // loop through sound XML data
    for (pugi::xml_node record = sound_directory.first_child(); record; record = record.next_sibling()) {
        // load ID
        uint8_t newID = record.attribute("id").as_int();
        
        // initialize sound
        Mix_Chunk* newSound = Mix_LoadWAV(record.child_value("filename"));
        // push to hashmap
        sound_map[newID] = newSound;

        // log ID and filename
        std::cout << "Sound ID: " << record.attribute("id").as_int();
        std::cout << ", Filename: " << record.child_value("filename") << std::endl;
    }
}

SoundManager::~SoundManager() {
    // clean up retained resources in hashmap
    for (std::pair<uint8_t, Mix_Chunk*> spair : sound_map) {
        Mix_FreeChunk(spair.second);
    }
}

#endif

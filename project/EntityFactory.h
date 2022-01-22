/*
 * descr: class definition for EntityFactory class. Generates Sprite and Static objects
 * author: Henry Dikeman
 */

// stdlib headers
#include <iostream>
#include <bitset>
#include <memory>
#include <array>
#include <stdio.h>
#include <stdbool.h>

// externlib headers
#include <SDL.h>

// internlib headers
#include "Sprite.h"
#include "Static.h"
#include "AssetManagers.h"

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

// *** WILL NEED TO BE DONE MORE SENSIBLY LATER *** // 
#define NUM_BG_TEXTURES (4)

class EntityFactory {
    private:
        std::shared_ptr<TextureManager> textureMngr;
        std::shared_ptr<SoundManager> soundMngr;
    public:
        // constructor
        EntityFactory(std::shared_ptr<TextureManager>& textureMngr, std::shared_ptr<SoundManager>& soundMngr);

        // destructor
        ~EntityFactory() {}

        // default sprite generation method
        std::shared_ptr<Sprite> generate_sprite(int x, int y);
        // id passed sprite generation function
        std::shared_ptr<Sprite> generate_sprite(int x, int y, uint8_t id);

        // default Static generation method
        std::shared_ptr<Static> generate_static(int x, int y);
        // id passed Static generation function
        std::shared_ptr<Static> generate_static(int x, int y, uint8_t id);

};

EntityFactory::EntityFactory(std::shared_ptr<TextureManager>& textureMngr, std::shared_ptr<SoundManager>& soundMngr) {
    // save texture and sound managers
    this->textureMngr = textureMngr;
    this->soundMngr = soundMngr;
}

// generate sprite of random id
std::shared_ptr<Sprite> EntityFactory::generate_sprite(int x, int y) {
    // call internal method with some randomized ID
    std::shared_ptr<Sprite> newSprite = generate_sprite(x, y, 0x01);

    // return generated sprite
    return newSprite;
}

// id passed generation method
std::shared_ptr<Sprite> EntityFactory::generate_sprite(int x, int y, uint8_t id){
    // generate new player
    std::shared_ptr<Sprite> newSprite = std::make_shared<Sprite>();

    // set ID
    newSprite->id() = id;
    // set health
    newSprite->health() = 100;
    newSprite->max_health() = 100;
    // set direction to default RIGHT
    newSprite->direction() = SpriteDirection::RIGHT;
    // set state to default IDLING
    newSprite->state() = SpriteState::IDLING;
    // set x and y
    newSprite->x() = x;
    newSprite->y() = y;
    // query for texture and set 
    newSprite->set_texture(
            textureMngr->query_texture(newSprite->id()),
            2 // NUM_CYCLES, change based on external file or standardize
            );
    // query for sound and set
    // NO SOUNDS FOR NOW
    // set drawsize
    newSprite->w() = textureMngr->get_grid_size();
    newSprite->h() = textureMngr->get_grid_size();

    // query for texture and set 
    newSprite->set_texture( textureMngr->query_texture(newSprite->id()) );
    // return Player
    return newSprite;
}

// generate sprite of random id
std::shared_ptr<Static> EntityFactory::generate_static(int x, int y) {
    // call internal method with some randomized ID
    int randID = 0xF0 + (rand() % NUM_BG_TEXTURES) + 1;
    std::shared_ptr<Static> newStatic = generate_static(x, y, randID);
    // return generated static object
    return newStatic;
}

// id passed generation method
std::shared_ptr<Static> EntityFactory::generate_static(int x, int y, uint8_t id) {
    // generate new player
    std::shared_ptr<Static> newStatic = std::make_shared<Static>();

    // set ID
    newStatic->id() = id;
    // set x and y
    newStatic->x() = x;
    newStatic->y() = y;
    // query for texture and set 
    newStatic->set_texture( textureMngr->query_texture(newStatic->id()) );
    // query for sound and set
    // NO SOUNDS FOR NOW
    // set drawsize
    newStatic->w() = textureMngr->get_grid_size();
    newStatic->h() = textureMngr->get_grid_size();
    // set source size to entire texture
    SDL_QueryTexture(newStatic->get_texture(), NULL, NULL, &(newStatic->src_w()), &(newStatic->src_h()));

    // return Player
    return newStatic;
}

#endif

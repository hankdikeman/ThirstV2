/*
 * descr: entity factory class
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
#include "Static.h"
#include "AssetManagers.h"

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

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

    // *** EVENTUALLY READ IN ATTRIBUTES FROM EXTERNAL FILE *** //
    // set ID
    newSprite->set_id(0x01);
    // set health
    newSprite->health() = 100;
    newSprite->mhealth() = 100;
    // set x and y
    newSprite->set_x(x);
    newSprite->set_y(y);
    // query for texture and set 
    newSprite->set_texture(
            textureMngr->query_texture(newSprite->get_id()),
            2 // NUM_CYCLES, change based on external file or standardize
            );
    // query for sound and set
    // NO SOUNDS FOR NOW
    // set drawsize
    newSprite->set_draw_w(textureMngr->get_grid_size());
    newSprite->set_draw_h(textureMngr->get_grid_size());

    // return Player
    return newSprite;
}

#endif

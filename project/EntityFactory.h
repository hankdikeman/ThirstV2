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
#include "Entities.h"
#include "AssetManagers.h"

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

class EntityFactory {
    private:
        TextureManager* textureMngr;
        SoundManager* soundMngr;
    public:
        // constructor
        EntityFactory(TextureManager* textureMngr, SoundManager* soundMngr);

        // destructor
        ~EntityFactory() {}

        // player generation method
        std::shared_ptr<Player>& generate_player();
        // default enemy generation method
        std::shared_ptr<Enemy>& generate_enemy();
        // id passed enemy generation method
        std::shared_ptr<Enemy>& generate_enemy(std::bitset<8> id);

};

EntityFactory::EntityFactory(TextureManager* textureMngr, SoundManager* soundMngr) {
    // save texture and sound managers
    this->textureMngr = textureMngr;
    this->soundMngr = textureMngr;
}

// player generation method
std::shared_ptr<Player>& generate_player() {
    // generate new player
    std::shared_ptr<Player> newPlayer = std::make_shared<Player>();

    // set health
    // set x and y
    // query for texture and set
    // query for sound and set
    // set drawsize

    // return Player
    return newPlayer;
}

// default enemy generation method
std::shared_ptr<Enemy>& generate_enemy() {
    // generate new player
    std::shared_ptr<Enemy> newEnemy = std::make_shared<Enemy>();

    // set health
    // set x and y
    // default query for texture and set
    // default query for sound and set
    // set drawsize

    // return Player
    return newEnemy;
}

// id passed enemy generation method
std::shared_ptr<Enemy>& generate_enemy(std::bitset<8> id){
    // generate new player
    std::shared_ptr<Enemy> newEnemy = std::make_shared<Enemy>();

    // set health
    // set x and y
    // query for texture and set
    // query for sound and set
    // set drawsize

    // return Player
    return newEnemy;
}

#endif

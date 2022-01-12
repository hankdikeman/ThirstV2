/*
 * descr: game engine Engine class definition
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
#include "Tilemap.h"
#include "EntityList.h"
#include "EntityFactory.h"

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

enum class GameState { 
    QUIT = -1,
    RUNNING = 0,
    PAUSED = 1
};

class Engine {
    private:
        std::unique_ptr<Tilemap> map;
        std::unique_ptr<EntityList> entList;
        std::unique_ptr<EntityFactory> entFact;

    public:
        void populate_map();
        GameState input();
        void step();
        void render(SDL_Renderer* renderer);
};

void Engine::populate_map() {

}

GameState Engine::input() {
    return GameState::RUNNING;
}

void Engine::step() {

}

void render(SDL_Renderer* renderer) {

}

#endif

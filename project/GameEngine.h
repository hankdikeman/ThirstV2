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
    RUNNING = 0
};

class Engine {
    private:
        std::shared_ptr<Tilemap> map;
        std::shared_ptr<EntityList> entList;
        std::shared_ptr<EntityFactory> entFact;

    public:
        // constructor
        Engine(std::shared_ptr<Tilemap> map, std::shared_ptr<EntityList> entList, std::shared_ptr<EntityFactory> entFact);

        // destructor
        ~Engine();

        // initialize tilemap with data
        void populate_map();
        // process input events
        GameState input();
        void handle_keypress(SDL_Event event);
        void handle_mousepress(SDL_Event event);

        // execute one game logic step
        void step();
        // render to screen
        void render(SDL_Renderer* renderer);
};

Engine::Engine(std::shared_ptr<Tilemap> map, std::shared_ptr<EntityList> entList, std::shared_ptr<EntityFactory> entFact) :
    map(map), entList(entList), entFact(entFact) {}

Engine::~Engine() {}

void Engine::populate_map() {
    // call seed generation function
    // procedurally generate sand texture
    // procedurally generate oases
        // make enemies for each oasis

}

// process input provided by user
GameState Engine::input() {
    // declare event object and pop from queue
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            // if quit, return quit code
            case SDL_QUIT:
                return GameState::QUIT;
                break;
            // if keydown, handle keydown event
            case SDL_KEYDOWN:
                this->handle_keypress(event);
                break;
            // mouse button functionality to be added later
            case SDL_MOUSEBUTTONDOWN:
                this->handle_mousepress(event);
                break;
        }
    }
    // default return is normal running
    return GameState::RUNNING;
}

// empty keypress handling function
void Engine::handle_keypress(SDL_Event event) {}

// empty mousepress handling function
void Engine::handle_mousepress(SDL_Event event) {}

// game logic step forward
void Engine::step() {
    // evaluate next steps for Enemies
    
    // perform scrolling operations

}

// render data onto background
void render(SDL_Renderer* renderer) {
    // clear screen
    SDL_RenderClear(renderer);

    // re-render background, potentially shifted
    // map->render_background();

    // render sprites within window
    // map->render_sprites();
}

#endif

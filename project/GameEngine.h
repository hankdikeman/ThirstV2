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

#define ENEMY_MOVE_DELAY (300.0f)
#define FRAME_SHIFT_DELAY (250.0f)

enum class GameState { 
    QUIT = -1,
    RUNNING = 0,
    PAUSED = 1
};

class Engine {
    private:
        // game data containers
        std::shared_ptr<Tilemap> map;
        std::shared_ptr<EntityList> entList;
        std::shared_ptr<EntityFactory> entFact;
        // engine state variables
        uint64_t last_logic_step;
        uint64_t last_frame_shift;

    public:
        // constructor
        Engine(std::shared_ptr<Tilemap> map, std::shared_ptr<EntityList> entList, std::shared_ptr<EntityFactory> entFact);

        // destructor
        ~Engine();

        // initialize tilemap with data
        void create_map(SDL_Renderer* renderer);
        void populate_map();
        // process input events
        GameState input();
        void handle_keypress(SDL_Event event);
        void handle_mousepress(SDL_Event event);
        // handle paused game
        void pause_game(SDL_Renderer* renderer);
        // execute one game logic step
        void step();
        // render to screen
        void render(SDL_Renderer* renderer);
};

Engine::Engine(std::shared_ptr<Tilemap> map, std::shared_ptr<EntityList> entList, std::shared_ptr<EntityFactory> entFact) :
    map(map), entList(entList), entFact(entFact) {}

Engine::~Engine() {}

void Engine::create_map(SDL_Renderer* renderer) {
    // initialize background texture and set as render target
    SDL_Texture* bg_texture = SDL_CreateTexture(
            renderer, 
            SDL_PIXELFORMAT_RGBA8888, 
            SDL_TEXTUREACCESS_TARGET, 
            map->width()*map->spacing(),
            map->height()*map->spacing()
            );
    SDL_SetRenderTarget(renderer, bg_texture);

    // construct background layer
    for (int i = 0; i < map->width(); i++) {
        for (int j = 0; j < map->height(); j++) {
            // generate desert static tiles at i,j
            std::shared_ptr<Static> newBg = entFact->generate_static(i,j);
            // add desert static tiles to map
            map->background(i,j) = newBg;
            // render desert to background texture
            SDL_RenderCopy(renderer, newBg->get_texture(), NULL, newBg->get_dstrect());
        }
    }

    // construct static decoration layer
    for (int i = 0; i < map->width(); i++) {
        for (int j = 0; j < map->height(); j++) {
            if (rand() % 100 < 5) {
                // generate desert static tiles at i,j
                std::shared_ptr<Static> newStat = entFact->generate_static(i,j,0xF5);
                // add desert static tiles to map
                map->statics(i,j) = newStat;
                // render desert to background texture
                SDL_RenderCopy(renderer, newStat->get_texture(), NULL, newStat->get_dstrect());
            }
        }
    }

    // move to tilemap
    map->background_texture() = bg_texture;

    // reset renderer target to window
    SDL_SetRenderTarget(renderer, NULL);
}

void Engine::populate_map() {
    // call seed generation function
    // procedurally generate sand texture
    // procedurally generate oases
        // make enemies for each oasis

    // *** DUMMY PLAYER INITIALIZATION *** //
    std::shared_ptr<Sprite> newPlayer = entFact->generate_sprite(6, 6, 0x01);
    map->sprite(6,6) = newPlayer;
    entList->get_player() = newPlayer;
    
    // *** DUMMY INITIALIZATION TO TEST *** //
    for (int idx = 0; idx < 10; idx++) {
        // generate new coords
        int newSprX = 67*59*13*idx % map->width(); int newSprY = 13*83*29*idx % map->height();
        // add to grid if not already occupied
        if (!map->is_occupied(newSprX, newSprY)) {
            // make new player shared ptr
            std::shared_ptr<Sprite> tempSprite = entFact->generate_sprite(newSprX, newSprY, 0x02);
            // add to tilemap and entity list
            map->sprite(newSprX, newSprY) = tempSprite;
            entList->add_enemy(tempSprite);
        }
    }

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
void Engine::handle_keypress(SDL_Event event) {
    // evaluate player position
    int player_x = entList->get_player()->x();
    int player_y = entList->get_player()->y();
    // move player based on command
    switch(event.key.keysym.scancode) {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
            map->sprite_up(player_x, player_y);
            break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
            map->sprite_left(player_x, player_y);
            break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
            map->sprite_down(player_x, player_y);
            break;
        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
            map->sprite_right(player_x, player_y);
            break;
    }
}

// empty mousepress handling function
void Engine::handle_mousepress(SDL_Event event) {
    // no mouse action for now
    return;
}

// pause game until player resumes
void Engine::pause_game(SDL_Renderer* renderer) {}

// game logic step forward
void Engine::step() {
    // check whether interval has passed for logic step
    uint64_t current_time = SDL_GetPerformanceCounter();
    float logic_elapsed = (current_time - this->last_logic_step) / (float) SDL_GetPerformanceFrequency() * 1000.0f;
    float frame_elapsed = (current_time - this->last_frame_shift) / (float) SDL_GetPerformanceFrequency() * 1000.0f;

    // set tilemap center
    map->set_center(entList->get_player()->x(), entList->get_player()->y());

    // shift frames if time has passed
    if (frame_elapsed > FRAME_SHIFT_DELAY) {
        // increment player frame
        entList->get_player()->increment_frame();
        for (std::shared_ptr<Sprite>& spr: entList->get_enemy_list()) {
            spr->increment_frame();
        }
        this->last_frame_shift = SDL_GetPerformanceCounter();
    }

    // take a logic step if enough time has passed
    if (logic_elapsed > ENEMY_MOVE_DELAY) {
        // check/update state of all enemies
        // act on state of all enemies
        // check health of all enemies

        // *** PASS OFF TO MOVEMENT FUNCTION IN SPRITE LATER *** // 
        // evaluate player position
        int player_x = entList->get_player()->x();
        int player_y = entList->get_player()->y();
        for (std::shared_ptr<Sprite>& spr: entList->get_enemy_list()) {
            // *** LATER APPROACH *** //
            // enemy->move(enemy_position, anchor_position, player_position)
            // get enemy position
            int spr_x = spr->x(); int spr_y = spr->y();
            // get distance
            int del_x = spr_x - player_x; int del_y = spr_y - player_y;
            // get magnitude of x and y offset
            if ( std::abs(del_x) > std::abs(del_y) ) {
                // move right if del_x is negative
                if (del_x < 0) { map->sprite_right(spr_x, spr_y); }
                // move left if del_x is positive
                else { map->sprite_left(spr_x, spr_y); }
            }
            else {
                // move down if del_y is negative
                if (del_y < 0) { map->sprite_down(spr_x, spr_y); }
                // move up if del_y is positive
                else { map->sprite_up(spr_x, spr_y); }
            }
        }
        this->last_logic_step = SDL_GetPerformanceCounter();
    }
}

// render data onto background
void Engine::render(SDL_Renderer* renderer) {
    // clear screen
    SDL_RenderClear(renderer);
    // re-render background, potentially shifted
    map->render_background(renderer);
    // render sprites within window
    map->render_sprites(renderer);
    // copy to screen
    SDL_RenderPresent(renderer);
}

#endif

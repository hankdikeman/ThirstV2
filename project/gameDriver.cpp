/*
 * descr: main driver file for Thirst
 * author: Henry Dikeman
 */

// C stdlib headers
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <array>
#include <algorithm>
#include <stdbool.h>

// core SDL header
#include <SDL.h>

// SDL window and image headers
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

// SDL input and event headers
#include <SDL_events.h>
#include <SDL_keyboard.h>

// internal lib headers
#include "Sprite.h"
#include "Static.h"
#include "Tilemap.h"
#include "EntityList.h"
#include "EntityFactory.h"
#include "GameEngine.h"

// window definitions`
#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (640)

// map info
#define GRID_SIZE (64)
#define MAP_WIDTH (64)
#define MAP_HEIGHT (64)

// define framerate
#define FRAMERATE (60.0f)

// declare internal funcs
bool init_game(void);
void kill_game(void);
bool load_resources(void);
void populate_data(void);

// window and renderer objects
SDL_Window* window;
SDL_Renderer* renderer;

// engine pointer
std::unique_ptr<Engine> engine;

// blank texture renderer
// SDL_Texture* texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 1024, 1024 );

// *** NEEDS PROPER ERROR CHECKING EVENTUALLY ** //
bool load_resources(void) {
    // make tilemap object
    std::shared_ptr<Tilemap> map = std::make_shared<Tilemap>(MAP_WIDTH, MAP_HEIGHT, GRID_SIZE, WINDOW_WIDTH/GRID_SIZE, WINDOW_HEIGHT/GRID_SIZE);

    // make entity list object
    std::shared_ptr<EntityList> entList = std::make_shared<EntityList>();

    // make and init texture manager
    std::shared_ptr<TextureManager> textureMngr = std::make_shared<TextureManager>(renderer, GRID_SIZE);
    textureMngr->init_textures();
    
    // make and init sound manager (not ready yet)
    std::shared_ptr<SoundManager> soundMngr = std::make_shared<SoundManager>();
    // soundMngr->init_sounds();

    // initialize EntityFactory with AssetManager object ptrs
    std::shared_ptr<EntityFactory> entFact = std::make_shared<EntityFactory>(textureMngr, soundMngr);

    // initialize engine object
    engine = std::make_unique<Engine>(map, entList, entFact);

    return true;
}

// *** NEEDS PROPER ERROR CHECKING EVENTUALLY *** //
bool init_game(void) {
    // initialize SDL and SDL_timer
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

    // init sound/music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    // init SDL_image
    IMG_Init(IMG_INIT_JPG);

    // create SDL window
    window = SDL_CreateWindow("ThirstV2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    // initialize renderer and set default color
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0xED, 0xC9, 0xAF, 0xFF);

    return true;
}

void game_loop(void) {
    // loop until quit command
    GameState game_state = GameState::RUNNING;
    while (game_state != GameState::QUIT) {
        // get start of loop time
        Uint64 start = SDL_GetPerformanceCounter();

        // check controller inputs and set gamestate
        game_state = engine->input();

        // check game state (paused, quit, etc), wait for action if not 0
        if (game_state == GameState::PAUSED) { engine->pause_game(renderer); }

        // game engine call (change AI vars like enemies)
        engine->step();

        // render call
        engine->render(renderer);

        // calculate elapsed time
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float) SDL_GetPerformanceFrequency() * 1000.0f;
        // delay to cap framerate
        SDL_Delay(std::max(static_cast<int>(16.666f - elapsedMS), 0));
    }
}

void populate_data(void) {
    // construct map texture
    engine->create_map(renderer);
    // populate game entities
    engine->populate_map();
}

void kill_game(void) {
    // global SDL vars deleted manually
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // quit SDL, SDL_image, SDL_mixer
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

int main(int argc, const char *argv[]) {
    // init game and load resources
    if (!init_game()) return 1;
    if (!load_resources()) return 1;
    // populate game map
    populate_data();
    // run game loop until quit
    game_loop();
    // free resources and end
    kill_game();
    return 0;
}

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
#include <stdio.h>

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
#include "Tile.h"
#include "Tilemap.h"
#include "EntityList.h"

// window definitions`
#define WINDOW_WIDTH (768)
#define WINDOW_HEIGHT (768)

// grid and spacing definitions
#define GRID_SIZE (64)
#define GRID_WIDTH (16)
#define GRID_HEIGHT (16)

// define framerate
#define FRAMERATE (60.0f)

// declare internal funcs
bool init_game(void);
void kill_game(void);
bool load_resources(void);
void populate_data(void);

// take out eventually (except for renderer and window)
// replace with manager classes
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* sprite;
Mix_Music* music;

// blank texture renderer
// SDL_Texture* texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 1024, 1024 );

bool load_resources(void) {
    // textureMngr = TextureManager();

    // *** MOVE TO TEXTURE INIT FUNCTION ** //
    // temporary var to load image
    SDL_Surface *temp;
    // load image to temp var
    temp = IMG_Load("Resources/PCSprite.png");
    // check for error
    if (!temp) {
        printf("error loading image\n");
        return false;
    }
    // format surfaces
    sprite = SDL_CreateTextureFromSurface(renderer, temp);
    // free temp
    SDL_FreeSurface(temp);
    // check for error
    if (!sprite) {
        printf("error converting image\n");
        return false;
    }

    // *** *** //

    // soundMngr = SoundManager();

    // *** MOVE TO MUSIC LOAD *** //
    // load music and play
    music = Mix_LoadMUS("Resources/jazzy.wav");
    // check for error
    if (!music) {
        printf("error loading music\n");
        return false;
    }
    // begin soundtrack
    // Mix_PlayMusic(music, -1);
    // *** *** //

    return true;
}

bool init_game(void) {
    // initialize SDL and SDL_timer
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)

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
    // loop until quit flag flipped
    while (!quit_flag) {
        // get start of loop time
        Uint64 start = SDL_GetPerformanceCounter();

        // check controller inputs
        // int gameState = InputHandler(EntityList, Tilemap);

        // game engine call (req: EntityList, Tilemap)
        // EngineStep(EntityList, Tilemap);

        // render call (req: renderer, EntityList, Tilemap)
        // ExecuteRender(renderer, EntityList, Tilemap);

        // calculate elapsed time
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float) SDL_GetPerformanceFrequency() * 1000.0f;
        // delay to cap framerate
        SDL_Delay(std::max(floor(16.666f - elapsedMS),0));
    }
}

void kill_game(void) {
    // destroy window and delete all SDL vars
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // clean up texture data (replace with textureMngr->clean_up();)
    SDL_DestroyTexture(sprite);

    // clean up audio data (replace with soundMngr->clean_up();)
    Mix_FreeMusic(music);

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

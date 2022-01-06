/*
 * descr: compilation test file for abstract class `Sprite`
 * author: Henry Dikeman
 */

// stdlib headers
#include <iostream>
#include <random>
#include <vector>
#include <array>
#include <stdbool.h>

// std::cout << text << std::endl;

// internal lib headers
#include "Sprite.h"
#include "Static.h"
#include "Tile.h"
#include "Tilemap.h"

// SDL Headers
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_events.h>
#include <SDL_keyboard.h>

// window definitions`
#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (640)

// grid and spacing definitions
#define GRID_SIZE (48)
#define GRID_WIDTH (20)
#define GRID_HEIGHT (20)

// sprite definitions
#define NUM_SPRITES (5)

// duration definitions
#define NUM_FRAMES (1000)
#define NUM_CYCLES (2)

// pointers to windows, textures, music
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

int main(int argc, const char *argv[]) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 8);

    // initialize video and timer, catch errors
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_JPG);

    // create SDL window and catch errors
    window = SDL_CreateWindow("ThirstV2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    // create SDL renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0xED, 0xC9, 0xAF, 0xFF);

    // temporary var to load image
    SDL_Surface *temp;
    // load image to temp var
    temp = IMG_Load("Resources/PCSprite.png");
    // format surfaces
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    // free temp
    SDL_FreeSurface(temp);

    // get size of texture to make sprite
    int picwidth, picheight;
    SDL_QueryTexture(texture, NULL, NULL, &picwidth, &picheight);

    // list of sprites
    Tilemap* map = new Tilemap(GRID_WIDTH, GRID_HEIGHT, GRID_SIZE);
    std::cout << "new Tilemap map: ";
    std::cout << map << std::endl;
    std::array<int,2> drawsize = {GRID_SIZE, GRID_SIZE};
    std::array<int,2> position = {0, 0};
    
    // initialize arrays
    for (int idx = 0; idx < NUM_SPRITES; idx++) {
        // add sprite to vector
        Sprite* tempSprite = new Sprite(position, drawsize, NUM_CYCLES, texture);
        std::cout << "new Sprite tempSprite: ";
        std::cout << tempSprite << std::endl;
        map->sprite(idx, idx) = tempSprite;
        // change position
        position[0] += GRID_SIZE;
        position[1] += GRID_SIZE;
    }

    // wait for key press before rendering further
    SDL_Event event;
    bool cont_req = false;
    while (!cont_req){
        // cycle through event queue and process
        while (SDL_PollEvent(&event)){
            switch(event.type) {
                // trigger if a key was pressed
                case SDL_KEYDOWN:
                    cont_req = true;
                    break;
            }
        }
    }

    // game loop
    for (int ctr = 0; ctr < NUM_FRAMES; ctr++) {
        // clear window
        SDL_RenderClear(renderer);
        // render loop
        for (int i = 0; i < GRID_WIDTH; i++) {
            for (int j = 0; j < GRID_HEIGHT; j++) {
                if (map->is_occupied(i, j)) {
                    // render sprite at i, j
                    SDL_RenderCopy(renderer, map->sprite(i,j)->get_texture(), map->sprite(i,j)->get_srcrect(), map->sprite(i,j)->get_dstrect());
                    if (ctr % 13 == 0) {
                        // increment frames
                        map->sprite(i,j)->increment_frame();
                    }
                    if (ctr % 25 == 0) {
                        // generate random motion
                        int move = distrib(gen);
                        // move sprite
                        if (move == 0) { map->sprite_inc_y(i,j); }
                        if (move == 1) { map->sprite_dec_y(i,j); }
                        if (move == 2) { map->sprite_inc_x(i,j); }
                        if (move == 3) { map->sprite_dec_x(i,j); }
                    }
                }
            }
        }

        // render all to window
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

    // show deleted pointer
    std::cout << "free Tilemap map: ";
    std::cout << map << std::endl;
    // free heap variables
    delete map;

    // destroy window and delete all SDL vars
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // quit SDL and SDL image
    IMG_Quit();
    SDL_Quit();

    return 0;
}

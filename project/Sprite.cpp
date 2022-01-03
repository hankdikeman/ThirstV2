/*
 * descr: compilation test file for abstract class `Sprite`
 * author: Henry Dikeman
 */

// stdlib headers
#include <array>
#include <vector>
#include <stdbool.h>
#include <iostream>

// std::cout << text << std::endl;

// internal lib headers
#include "Sprite.h"

// SDL Headers
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_events.h>
#include <SDL_keyboard.h>

// window definitions`
#define WINDOW_WIDTH (720)
#define WINDOW_HEIGHT (640)

// sprite definitions
#define SPRITE_SIZE (32)
#define NUM_SPRITES (20)

// duration definitions
#define NUM_FRAMES (10)

// pointers to windows, textures, music
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

int main(int argc, const char *argv[]) {
    // initialize video and timer, catch errors
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_JPG);

    // create SDL window and catch errors
    window = SDL_CreateWindow("ThirstV2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    // create SDL renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0xED, 0xC9, 0xAF, 0xFF);

    // temporary var to load image
    SDL_Surface *temp;
    // load image to temp var
    temp = IMG_Load("Resources/CH_Sprite.jpeg");
    // format surfaces
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    // free temp
    SDL_FreeSurface(temp);

    // get size of texture to make sprite
    int picwidth, picheight;
    SDL_QueryTexture(texture, NULL, NULL, &picwidth, &picheight);

    // list of sprites
    std::vector<Sprite> spritelist;
    std::array<int,2> size = {32, 32};
    std::array<int,2> position = {0, 0};
    
    // initialize arrays
    for (int idx = 0; idx < NUM_SPRITES; idx++) {
        // add sprite to vector
        Sprite newSprite = Sprite(position, size, texture);
        spritelist.push_back(newSprite);
        // change position
        position[0] += 32;
        position[1] += 32;
    }

    // game loop
    for (int ctr = 0; ctr < NUM_FRAMES; ctr++) {
        // clear window
        SDL_RenderClear(renderer);
        // render loop
        for (int idx = 0; idx < NUM_SPRITES; idx++) {
            SDL_RenderCopy(renderer, spritelist[idx].get_texture(), spritelist[idx].get_srcrect(), spritelist[idx].get_dstrect());
        }

        // render all to window
        SDL_RenderPresent(renderer);
        SDL_Delay(2);

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
    }

    // destroy window and delete all SDL vars
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // quit SDL and SDL image
    IMG_Quit();
    SDL_Quit();

    return 0;
}

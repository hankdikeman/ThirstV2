/*
 * descr: compilation test file for abstract class `Sprite`
 * author: Henry Dikeman
 */

// stdlib headers
#include <array>
#include <random>
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
#define SPRITE_SIZE (64)
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
    std::uniform_int_distribution<> distrib(-5, 5);

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
    temp = IMG_Load("Resources/PCSprite.png");
    // format surfaces
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    // free temp
    SDL_FreeSurface(temp);

    // get size of texture to make sprite
    int picwidth, picheight;
    SDL_QueryTexture(texture, NULL, NULL, &picwidth, &picheight);

    // list of sprites
    std::vector<Sprite> spritelist;
    std::array<int,2> drawsize = {SPRITE_SIZE, SPRITE_SIZE};
    std::array<int,2> position = {0, 0};
    
    // initialize arrays
    for (int idx = 0; idx < NUM_SPRITES; idx++) {
        // add sprite to vector
        Sprite newSprite = Sprite(position, drawsize, NUM_CYCLES, texture);
        spritelist.push_back(newSprite);
        // change position
        position[0] += SPRITE_SIZE;
        position[1] += SPRITE_SIZE;
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
        for (int idx = 0; idx < NUM_SPRITES; idx++) {
            SDL_RenderCopy(renderer, spritelist[idx].get_texture(), spritelist[idx].get_srcrect(), spritelist[idx].get_dstrect());
            if (ctr % 10 == 0) {
                // increment sprite frame
                spritelist[idx].increment_frame();
                // random width
                spritelist[idx].set_width(spritelist[idx].get_width() + distrib(gen));
                // random height
                spritelist[idx].set_height(spritelist[idx].get_height() + distrib(gen));
                // random x
                spritelist[idx].set_xpos(spritelist[idx].get_xpos() + distrib(gen));
                // random y
                spritelist[idx].set_ypos(spritelist[idx].get_ypos() + distrib(gen));
            }
        }

        // render all to window
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
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

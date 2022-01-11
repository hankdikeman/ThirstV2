/*
 * descr: compilation test file for abstract class `Sprite`
 * author: Henry Dikeman
 */

// stdlib headers
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <array>
#include <stdbool.h>

// std::cout << text << std::endl;

// internal lib headers
#include "Static.h"
#include "Tile.h"
#include "Tilemap.h"
#include "EntityList.h"
#include "Entities.h"
#include "AssetManagers.h"

// SDL Headers
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_events.h>
#include <SDL_keyboard.h>

// window definitions`
#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (640)

// grid and spacing definitions
#define GRID_SIZE (64)
#define GRID_WIDTH (27)
#define GRID_HEIGHT (27)

// sprite definitions
#define NUM_SPRITES (5)

// duration definitions
#define NUM_FRAMES (250)
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

    // make tilemap object
    Tilemap* map = new Tilemap(GRID_WIDTH, GRID_HEIGHT, GRID_SIZE);
    std::cout << "new Tilemap map: ";
    std::cout << map << std::endl;
    // make entity list object
    EntityList* elist = new EntityList();
    std::cout << "new EntityList elist: ";
    std::cout << elist << std::endl;
    // make texture manager
    TextureManager* textureMngr = new TextureManager();
    textureMngr->init_textures(renderer);
    std::cout << "new TextureManager textureMngr: ";
    std::cout << textureMngr << std::endl;

    // make drawsize and position arrays
    std::array<int,2> drawsize = {GRID_SIZE, GRID_SIZE};
    std::array<int,2> position = {0, 0};
    
    // initialize arrays
    for (int idx = 0; idx < NUM_SPRITES; idx++) {
        // make new sprite shared_ptr
        std::shared_ptr<Sprite> tempSprite = std::make_shared<Sprite>();

        // set ID to player
        tempSprite->set_id(0b00000001);

        // add texture data and drawsize data
        tempSprite->set_texture(textureMngr->query_texture(tempSprite->get_id()), NUM_CYCLES);
        tempSprite->set_drawsize(drawsize);
        // add position data
        tempSprite->set_position(position);

        // add to tilemap and entity list
        map->sprite(idx, idx) = tempSprite;
        elist->add_enemy(tempSprite);

        // change position
        position[0] += 1;
        position[1] += 1;
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

    // control vars
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool window_close_req = false;
    int ctr = 0;

    // game loop
    while (!window_close_req) {
        // increment cycle counter
        ctr++;
        // cycle through event queue and process
        while (SDL_PollEvent(&event)){
            switch(event.type) {
                // quit game
                case SDL_QUIT:
                    window_close_req = true;
                    break;
                // trigger if a key was pressed
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            up = true;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            left = true;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            down = true;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            right = true;
                            break;
                    }
                    // move loop for move command
                    for (std::shared_ptr<Sprite>& spr : elist->get_enemy_list()) {
                        // get position data
                        int spr_x = spr->get_x(); int spr_y = spr->get_y();
                        // process movement
                        if (left) { map->sprite_left(spr_x,spr_y); }
                        if (right) { map->sprite_right(spr_x,spr_y); }
                        if (up) { map->sprite_up(spr_x,spr_y); }
                        if (down) { map->sprite_down(spr_x,spr_y); }
                    }
                    // reset control vars
                    up = false;
                    down = false;
                    left = false;
                    right = false;
                    break;
            }
        }
        SDL_RenderClear(renderer);
        // render loop
        int i = 0; int j = 0;
        for (i = 0; i < GRID_WIDTH; i++) {
            for (j = 0; j < GRID_HEIGHT; j++) {
                if (map->is_occupied(i, j)) {
                    // render sprite at i, j
                    map->draw(renderer, i, j);
                    if (ctr % 13 == 0) {
                        // increment frames
                        map->sprite(i,j)->increment_frame();
                    }
                }
            }
        }
        SDL_RenderPresent(renderer);
        // render all to window
        SDL_Delay(20);
    }

    // make entity list object
    std::cout << "free EntityList elist: ";
    std::cout << elist << std::endl;
    // show deleted pointer
    std::cout << "free Tilemap map: ";
    std::cout << map << std::endl;
    // free heap variables
    delete map;
    delete elist;

    // show deleted resource handler
    std::cout << "free TextureManager textureMngr: ";
    std::cout << textureMngr << std::endl;
    // delete textureMngr (with internal cleanup)
    delete textureMngr;

    // destroy window and delete all SDL vars
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // quit SDL and SDL image
    IMG_Quit();
    SDL_Quit();

    return 0;
}

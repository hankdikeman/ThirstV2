// C stdlib header
#include <stdio.h>
#include <stdbool.h>

// core SDL header
#include <SDL.h>

// window and image headers
#include <SDL_timer.h>
#include <SDL_image.h>

// input and event headers
#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_mouse.h>

// defining window and scrolling characteristics
#define WINDOW_WIDTH (720)
#define WINDOW_HEIGHT (640)
#define SCROLL_SPEED (800)

int main(void) {
        // initialize video and timer, catch errors
        if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
            printf("error initializing SDL: %s\n", SDL_GetError());
            return 1;
        }
        printf("initialization successful!\n");

        // create SDL window and catch errors
        SDL_Window* win = SDL_CreateWindow("ThirstV2",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        if (!win) {
            printf("error during window creation: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }

        // create renderer
        Uint32 render_flags = SDL_RENDERER_ACCELERATED;
        SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
        if (!rend) {
            printf("error during renderer creation: %s\n", SDL_GetError());
            SDL_DestroyWindow(win);
            SDL_Quit();
            return 1;
        }

        // load image into memory
        SDL_Surface* surface = IMG_Load("Resources/SexyCactus.png");
        if (!surface) {
            printf("error creating image surface");
            SDL_DestroyRenderer(rend);
            SDL_DestroyWindow(win);
            SDL_Quit();
        }

        // load image data into graphics hardware
        SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
        SDL_FreeSurface(surface);
        if (!tex) {
            printf("error creating texture object");
            SDL_DestroyRenderer(rend);
            SDL_DestroyWindow(win);
            SDL_Quit();
        }

        // poll for end events so window can be seen
        SDL_Event e;
        bool quit = false;
        while (!quit){
            while (SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                    quit = true;
                }
                if (e.type == SDL_KEYDOWN){
                    quit = true;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN){
                    quit = true;
                }
            }
        }

        // sprite struct
        SDL_Rect dest;
        SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

        // position sprite
        dest.x = (WINDOW_WIDTH - dest.w) / 2;
        float y_pos = WINDOW_HEIGHT;

        // animation loop
        while(dest.y >= -dest.h) {
            // clear window
            SDL_RenderClear(rend);

            // set sprite position
            dest.y = (int) y_pos;

            // draw new image to window
            SDL_RenderCopy(rend, tex, NULL, &dest);
            SDL_RenderPresent(rend);

            // update position
            y_pos -= (float) SCROLL_SPEED / 60;

            // small delay between animations
            SDL_Delay(1000/60);
        }

        //// clear window and draw image
        //SDL_RenderClear(rend);
        //SDL_RenderCopy(rend, tex, NULL, NULL);
        //SDL_RenderPresent(rend);
//

        // destroy window and delete all SDL vars
        SDL_DestroyTexture(tex);
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();

        return 0;
    }

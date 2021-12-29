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
#define Y_SPEED (120)
#define X_SPEED (240)
#define FRAMERATE (60)

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

        // sprite struct
        SDL_Rect dest;

        // load with texture and scale
        SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
        dest.w /= 8;
        dest.h /= 8;

        // start in center of screen
        float x_pos = (WINDOW_WIDTH - dest.w) / 2;
        float y_pos = (WINDOW_HEIGHT - dest.h) / 2;

        // initial velocity
        float x_vel = X_SPEED;
        float y_vel = Y_SPEED;

        // poll for end events and perform movement loop
        SDL_Event e;
        bool window_close_req = false;
        while (!window_close_req){
            // cycle through event queue and process
            while (SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                    window_close_req = true;
                }
                if (e.type == SDL_KEYDOWN){
                    window_close_req = true;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN){
                    window_close_req = true;
                }
            }

            // move object and check for collisions
            if (x_pos <= 0) {
                x_pos = 0;
                x_vel = -x_vel;
            }
            if (y_pos <= 0) {
                y_pos = 0;
                y_vel = -y_vel;
            }
            if (x_pos >= WINDOW_WIDTH - dest.w) {
                x_pos = WINDOW_WIDTH - dest.w;
                x_vel = -x_vel;
            }
            if (y_pos >= WINDOW_HEIGHT - dest.h) {
                y_pos = WINDOW_HEIGHT - dest.h;
                y_vel = -y_vel;
            }

            // update sprite position
            x_pos += x_vel / FRAMERATE;
            y_pos += y_vel / FRAMERATE;

            // update positions in structure
            dest.x = (int) x_pos;
            dest.y = (int) y_pos;

            // clear window and complete new render
            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, tex, NULL, &dest);
            SDL_RenderPresent(rend);
            
            // delay to set frame rate
            SDL_Delay(1000/FRAMERATE);
        }

        // destroy window and delete all SDL vars
        SDL_DestroyTexture(tex);
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();

        return 0;
    }

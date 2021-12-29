#include <stdio.h>
#include <SDL.h>
#include <SDL_timer.h>

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
                                            640, 480, 0);
        if (!win) {
            printf("error during window creation: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }

        // delay to make window visible
        SDL_Delay(5000);

        // destroy window and delete all SDL vars
        SDL_DestroyWindow(win);
        SDL_Quit();

        return 0;
    }

#include <stdio.h>
#include <SDL.h>

int main(void) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            printf("error initializing SDL: %s\n", SDL_GetError());
            return 1;
        }
        printf("initialization successful!\n");

        SDL_Quit();

        return 0;
    }

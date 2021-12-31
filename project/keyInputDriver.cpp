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

// define sprite size
#define SPRITE_SIZE (32)

// define speed and framerate
#define Y_SPEED (240)
#define X_SPEED (240)
#define FRAMERATE (60)

// declare internal funcs
bool init_game(void);
void kill_game(void);
bool load_resources(void);

// pointers to windows and surfaces
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* winSurface;
SDL_Surface* sprite;
SDL_Rect dest = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH/8, WINDOW_HEIGHT/8};

bool load_resources(void) {
    // temporary var to load image
    SDL_Surface *temp;
    // load image to temp var
    temp = SDL_LoadBMP("Resources/CactusHero.bmp");
    // check for error
    if (!temp) {
        printf("error loading image\n");
        return false;
    }

    // format surfaces
    sprite = SDL_ConvertSurface(temp, winSurface->format, 0);
    // free temp
    SDL_FreeSurface(temp);
    // check for error
    if (!sprite) {
        printf("error converting image\n");
        return false;
    }
    return true;
}

bool init_game(void) {
    // initialize video and timer, catch errors
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return false;
    }

    // create SDL window and catch errors
    window = SDL_CreateWindow("ThirstV2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        printf("error during window creation: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    // create SDL renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("error during renderer creation: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    return true;
}

void game_loop(void) {
    // start in center of screen
    float x_pos = dest.x;
    float y_pos = dest.y;
    // initial velocity
    float x_vel = X_SPEED;
    float y_vel = Y_SPEED;
    // movement direction flags
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    // poll for end events and perform movement loop
    SDL_Event event;
    bool window_close_req = false;
    while (!window_close_req){
        // cycle through event queue and process
        while (SDL_PollEvent(&event)){
            switch(event.type) {
                // process quit request
                case SDL_QUIT:
                    window_close_req = true;
                    break;
                // process movement key presses
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
                    break;
                case SDL_KEYUP:
                    switch(event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            up = false;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            left = false;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            down = false;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            right = false;
                            break;
                    }
                    break;
            }
        }
        // determine velocity
        x_vel = y_vel = 0;
        if (up && !down) y_vel = -Y_SPEED;
        if (down && !up) y_vel = Y_SPEED;
        if (left && !right) x_vel = -X_SPEED;
        if (right && !left) x_vel = X_SPEED;
        // move object and check for collisions
        if (x_pos <= 0) x_pos = 0;
        if (y_pos <= 0) y_pos = 0;
        if (x_pos >= WINDOW_WIDTH - dest.w) x_pos = WINDOW_WIDTH - dest.w;
        if (y_pos >= WINDOW_HEIGHT - dest.h) y_pos = WINDOW_HEIGHT - dest.h;
        // update sprite position
        x_pos += x_vel / FRAMERATE;
        y_pos += y_vel / FRAMERATE;
        // update positions in structure
        dest.x = (int) x_pos;
        dest.y = (int) y_pos;
        // black out screen
        SDL_FillRect(winSurface,NULL,SDL_MapRGB(winSurface->format,0xED, 0xC9, 0xAF));
        // clear window and complete new render
        SDL_BlitScaled(sprite, NULL, winSurface, &dest);
        SDL_UpdateWindowSurface(window);
        // delay to set frame rate
        SDL_Delay(1000/FRAMERATE);
    }
}

void kill_game(void) {
    // destroy window and delete all SDL vars
    SDL_FreeSurface(sprite);
    SDL_FreeSurface(winSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    // init game and load resources
    if (!init_game()) return 1;
    if (!load_resources()) return 1;
    // add sprite initially to screen
    SDL_FillRect(winSurface,NULL,SDL_MapRGB(winSurface->format,0xED, 0xC9, 0xAF));
    SDL_BlitScaled(sprite, NULL, winSurface, &dest);
    SDL_UpdateWindowSurface(window);
    // run game loop until quit
    game_loop();
    // free resources and end
    kill_game();
    return 0;
}

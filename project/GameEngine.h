/*
 * descr: game engine class Engine
 * author: Henry Dikeman
 */

// stdlib headers
#include <iostream>
#include <bitset>
#include <memory>
#include <array>
#include <stdbool.h>

// externlib headers
#include <SDL.h>

// internlib headers

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

enum GameState { running, paused, quit };

class Engine {
    private:

    public:
        void populate_map() {}
        GameState input() { return 0; }
        void step() {}
        void render() {}
};

#endif

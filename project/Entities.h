/*
 * descr: header file for Sprite entity class. Animations which have repeated cycles
 * author: Henry Dikeman
 */

// stdlib headers
#include <array>

// externlib headers
#include <SDL.h>

// internlib headers
#include "Sprite.h"

#ifndef ENTITIES_H
#define ENTITIES_H

// define enemy states
enum EnemyState { idling, attacking, fleeing };

class Enemy : public Sprite {
    private:
        EnemyState state;
        int health;
        int mhealth;

    public:
        // constructor
        Enemy() {}

        // destructor
        ~Enemy() {}
        
        // state setter and getter
        EnemyState get_direction() { return state; }
        void set_direction(EnemyState dir) { this->state = state; }

        // health setter and getter
        int get_health() { return health; }
        void set_health(int health) { this->health = health; }
        void add_health(int increment) { 
            this->health += increment; 
            this->health %= mhealth;
        }
        
        // max health setter and getter
        int get_mhealth() { return mhealth; }
        void set_mhealth(int mhealth) { this->mhealth = mhealth; }
        void add_mhealth(int increment) { this->mhealth += increment; }

        // init health method
        void init_health(int mhealth) {
            this->mhealth = mhealth;
            this->health = mhealth;
        }
};

class Player : public Sprite {
    private:
        int health;
        int mhealth;

    public:
        // constructor
        Player() {}

        // destructor
        ~Player() {}
        
        // health setter and getter
        int get_health() { return health; }
        void set_health(int health) { this->health = health; }
        void add_health(int increment) { 
            this->health += increment; 
            this->health %= mhealth;
        }

        // max health setter and getter
        int get_mhealth() { return mhealth; }
        void set_mhealth(int mhealth) { this->mhealth = mhealth; }
        void add_mhealth(int increment) { this->mhealth += increment; }

        // init health method
        void init_health(int mhealth) {
            this->mhealth = mhealth;
            this->health = mhealth;
        }
};

#endif

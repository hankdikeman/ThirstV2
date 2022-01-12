/*
 * descr: header file for Sprite entity class. Animations which have repeated cycles
 * author: Henry Dikeman
 */

// stdlib headers
#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <algorithm>
#include <stdbool.h>

// externlib headers
#include <SDL.h>

// internlib headers
#include "Drawable.h"
#include "Sprite.h"

#ifndef ENTITYLIST_H
#define ENTITYLIST_H

class EntityList {
    private:
        std::vector< std::shared_ptr<Sprite> > enemy_list;
        std::shared_ptr<Sprite> player;
    public:
        // constructors
        EntityList();
        EntityList(std::shared_ptr<Sprite>& player);
        EntityList(std::shared_ptr<Sprite>& player, std::vector<std::shared_ptr<Sprite> >& enemy_list);

        // destructor
        ~EntityList() {}

        // getters
        std::vector<std::shared_ptr<Sprite> >& get_enemy_list() { return enemy_list; }
        std::shared_ptr<Sprite>& get_enemy(int idx) { return enemy_list[idx]; }
        std::shared_ptr<Sprite>& get_player() { return player; }

        // setters
        void add_enemy(std::shared_ptr<Sprite> enemy) { enemy_list.push_back(enemy); }

        // delete methods
        bool delete_enemy(std::shared_ptr<Sprite>& enemy);
};

// empty constructor
EntityList::EntityList() {}

// player-only constructor
EntityList::EntityList(std::shared_ptr<Sprite>& player) :
    player(player) {}

// enemy list and player constructor
EntityList::EntityList(std::shared_ptr<Sprite>& player, std::vector<std::shared_ptr<Sprite> >& enemy_list) :
    enemy_list(enemy_list),
    player(player) {}

bool EntityList::delete_enemy(std::shared_ptr<Sprite>& enemy) {
    // store initial size
    int original_size = enemy_list.size();
    // erase remove to remove enemies
    enemy_list.erase(std::remove(enemy_list.begin(), enemy_list.end(), enemy), enemy_list.end());
    // return success flag
    return original_size == enemy_list.size()-1;
}

#endif

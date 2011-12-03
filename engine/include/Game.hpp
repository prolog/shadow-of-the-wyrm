#pragma once
#include <vector>
#include "DisplayTile.hpp"
#include "Race.hpp"
#include "Class.hpp"
#include "World.hpp"

class Game
{
  public:
    static Game* get_instance();

    void set_races(const RaceMap& game_races);
    const RaceMap& get_races_ref() const;

    void set_classes(const ClassMap& game_classes);
    const ClassMap& get_classes_ref() const;

    void set_tile_info(const std::vector<DisplayTile>& game_tiles);
    const std::vector<DisplayTile>& get_tile_info_ref() const;

    void create_new_world(CreaturePtr creature);
    void go(); // main game loop

    // Additional operations will eventually be needed to do many
    // worlds and rebirth.

  protected:
    friend class SavageLandsEngine;
    Game();
    ~Game();

    static Game* game_instance;

    // The races, classes, and items are not the actual in-game items;
    // they're the template upon which the in-game items are built.
    RaceMap races;
    ClassMap classes;
    std::vector<DisplayTile> tile_info; // vector because we can get constant-time lookup by virtue of sequential tile types.
    // ItemMap items;

    // The current list of game worlds.
    std::vector<WorldPtr> worlds;
};

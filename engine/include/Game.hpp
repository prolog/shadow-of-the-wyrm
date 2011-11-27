#pragma once
#include <vector>
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

  protected:
    friend class SavageLandsEngine;
    Game();
    ~Game();

    static Game* game_instance;

    // The races, classes, and items are not the actual in-game items;
    // they're the template upon which the in-game items are built.
    RaceMap races;
    ClassMap classes;
    // ItemMap items;

    // The current list of game worlds.
    std::vector<WorldPtr> worlds;
};

#pragma once
#include "Race.hpp"
#include "Class.hpp"

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

    RaceMap races;
    ClassMap classes;
};

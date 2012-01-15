#pragma once
#include <vector>
#include "ActionManager.hpp"
#include "Directions.hpp"
#include "DisplayTile.hpp"
#include "Display.hpp"
#include "Item.hpp"
#include "Race.hpp"
#include "Class.hpp"
#include "World.hpp"

class Game
{
  public:
    static Game* instance();

    void set_display(DisplayPtr display);
    DisplayPtr get_display() const;

    void set_races(const RaceMap& game_races);
    const RaceMap& get_races_ref() const;

    void set_classes(const ClassMap& game_classes);
    const ClassMap& get_classes_ref() const;
    
    void set_items(const ItemMap& game_items);
    const ItemMap& get_items_ref() const;

    void set_tile_display_info(const std::vector<DisplayTile>& game_tiles);
    const std::vector<DisplayTile>& get_tile_display_info_ref() const;

    CreaturePtr get_current_player() const;

    void create_new_world(CreaturePtr creature);
    void go(); // main game loop

    // Additional operations will eventually be needed to do many
    // worlds and rebirth.

  protected:
    friend class SavageLandsEngine;
    friend class CommandProcessor;

    Game();
    ~Game();

    // Game commands - protected, so they should only be called by SavageLandsEngine
    // or CommandProcessor.

    // Quits the game.  Right now this just sets a boolean flag in the game loop to be false, so there will need to be
    // additional work done later to compensate for pending actions, etc.
    void quit();

    bool keep_playing;
    static Game* game_instance;

    // The races, classes, and items are not the actual in-game items;
    // they're the template upon which the in-game items are built.
    DisplayPtr display;
    RaceMap races;
    ClassMap classes;
    ItemMap items;
    std::vector<DisplayTile> tile_info; // vector because we can get constant-time lookup by virtue of sequential tile types.
    // ItemMap items;

    // The current list of game worlds.
    std::vector<WorldPtr> worlds;

    // The current list of players (one per game world).
    std::vector<CreaturePtr> players;

    // The current world index in the list of worlds.
    uint current_world_ix;

    // The currently-loaded map
    MapPtr current_map;

    // The action manager
    ActionManager actions;
};

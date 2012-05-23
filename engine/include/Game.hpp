#pragma once
#include <vector>
#include "ActionManager.hpp"
#include "Class.hpp"
#include "CreatureGenerationValues.hpp"
#include "Deity.hpp"
#include "Directions.hpp"
#include "DisplayTile.hpp"
#include "Display.hpp"
#include "Item.hpp"
#include "MapRegistry.hpp"
#include "Race.hpp"
#include "World.hpp"

class Game
{
  public:
    static Game* instance();

void FIXME_REMOVE_THIS_FUNCTION(CreaturePtr player);

    void set_display(DisplayPtr display);
    DisplayPtr get_display() const;

    void set_map_registry(const MapRegistry& new_map_registry);
    MapRegistry& get_map_registry_ref();

    void set_deities(const DeityMap& game_deities);
    const DeityMap& get_deities_ref() const;
    
    void set_races(const RaceMap& game_races);
    const RaceMap& get_races_ref() const;

    void set_classes(const ClassMap& game_classes);
    const ClassMap& get_classes_ref() const;
    
    void set_creatures(const CreatureMap& game_creatures);
    const CreatureMap& get_creatures_ref() const;
    
    void set_creature_generation_values(const CreatureGenerationValuesMap& game_cgv);
    const CreatureGenerationValuesMap& get_creature_generation_values_ref() const;
    
    void set_items(const ItemMap& game_items);
    const ItemMap& get_items_ref() const;
    
    MapPtr get_current_map();

    void set_tile_display_info(const std::vector<DisplayTile>& game_tiles);
    const std::vector<DisplayTile>& get_tile_display_info_ref() const;

    CreaturePtr get_current_player() const;

    void create_new_world(CreaturePtr creature);
    void go(); // main game loop

    // Additional operations will eventually be needed to do many
    // worlds and rebirth.

  protected:
    friend class SavageLandsEngine;
    friend class CreatureDeathManager;
    friend class PlayerDeathManager;
    friend class MovementManager;
    friend class ItemManager;
    friend class CommandProcessor;
    friend class EquipmentCommandProcessor;

    Game();
    ~Game();

    // Game commands - protected, so they should only be called by SavageLandsEngine
    // or CommandProcessor.

    // Quits the game.  Right now this just sets a boolean flag in the game loop to be false, so there will need to be
    // additional work done later to compensate for pending actions, etc.
    void quit();
    
    // Re-gets the map, and restarts the game loop
    void reload_map();
    
    // Update the physical display
    void update_display(CreaturePtr creature, MapPtr map);

    // Set the map to be used as the current for the game's computational purposes.
    void set_current_map(MapPtr map);
  
    bool keep_playing;
    bool reload_game_loop;
    static Game* game_instance;

    // The races, classes, and items are not the actual in-game items;
    // they're the template upon which the in-game items are built.
    DisplayPtr display;
    MapRegistry map_registry;
    DeityMap deities;
    RaceMap races;
    ClassMap classes;
    CreatureMap creatures;
    CreatureGenerationValuesMap creature_generation_values;
    ItemMap items;
    std::vector<DisplayTile> tile_info; // vector because we can get constant-time lookup by virtue of sequential tile types.

    // The current list of game worlds.
    std::vector<WorldPtr> worlds;

    // The current list of players (one per game world).
    std::vector<CreaturePtr> players;

    // The current world index in the list of worlds.
    uint current_world_ix;

    // The currently-loaded map's ID, used to look up the map in the registry.
    std::string current_map_id;

    // The action manager
    ActionManager actions;
};

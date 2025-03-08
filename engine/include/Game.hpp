#pragma once
#include <chrono>
#include <vector>
#include "ActionCoordinator.hpp"
#include "ActionManager.hpp"
#include "Class.hpp"
#include "CreatureGenerationValues.hpp"
#include "Deity.hpp"
#include "DeityActionManager.hpp"
#include "Directions.hpp"
#include "DisplayTile.hpp"
#include "Display.hpp"
#include "Features.hpp"
#include "Item.hpp"
#include "ISerializable.hpp"
#include "LoadedMapDetails.hpp"
#include "MapRegistry.hpp"
#include "Mortuary.hpp"
#include "Music.hpp"
#include "Quests.hpp"
#include "Race.hpp"
#include "ScriptEngine.hpp"
#include "Settings.hpp"
#include "Sound.hpp"
#include "Spell.hpp"
#include "StartingLocation.hpp"
#include "World.hpp"
#include "WorldTimeKeeper.hpp"

#include "CursesDisplay.hpp"

class Game : public ISerializable
{
  public:
    static Game& instance()
    {
      static Game game;
      return game;
    }

    void set_title_text(const std::string& new_title_text);
    void set_loading();
    void set_ready();
    bool get_loading() const;

    void set_requires_redraw(const bool new_requires_redraw);
    bool get_requires_redraw() const;

    void set_settings(const Settings& settings);
    void set_display_settings();
    void set_world_settings();
    Settings& get_settings_ref();

    void set_display(DisplayPtr display);
    DisplayPtr get_display() const;

    void set_sound(SoundPtr sound);
    SoundPtr get_sound() const;
    SoundPtr get_sound(CreaturePtr creature);

    void set_sound_effects(const std::map<std::pair<std::string, std::string>, std::string>& sound_effects);
    const std::map<std::pair<std::string, std::string>, std::string>& get_sound_effects_cref() const;

    void set_music(const Music& new_music);
    Music get_music() const;
    const Music& get_music_cref() const;

    void set_map_registry(const MapRegistry& new_map_registry);
    MapRegistry& get_map_registry_ref();

    void set_deities(const DeityMap& game_deities);
    DeityMap& get_deities_ref();
    const DeityMap& get_deities_cref() const;
    bool do_deities_exist() const;

    void set_races(const RaceMap& game_races);
    const RaceMap& get_races_ref() const;

    void set_classes(const ClassMap& game_classes);
    const ClassMap& get_classes_ref() const;
    
    void set_creatures(const CreatureMap& game_creatures);
    const CreatureMap& get_creatures_ref() const;

    void set_spells(const SpellMap& game_spells);
    const SpellMap& get_spells_ref();
    
    void set_creature_generation_values(const CreatureGenerationValuesMap& game_cgv);
    CreatureGenerationValuesMap& get_creature_generation_values_ref();

    void set_item_generation_values(const GenerationValuesMap& game_igv);
    GenerationValuesMap& get_item_generation_values_ref();
    
    void set_items(const ItemMap& game_items);
    const ItemMap& get_items_ref() const;

    void set_configurable_features(const FeatureMap& game_features);
    const FeatureMap& get_configurable_features_ref() const;

    void set_custom_maps(const std::vector<MapPtr>& custom_maps);
    // No getter - once the maps are in the registry, there's no way to determine which are custom.
    // (Realistically, nor should there need to be.)
    
    MapPtr get_current_map() const;
    bool get_is_current_map(MapPtr map) const;

    void set_tile_display_info(const std::vector<DisplayTile>& game_tiles);
    const std::vector<DisplayTile>& get_tile_display_info_ref() const;

    void set_trap_info(const std::vector<TrapPtr>& game_traps);
    const std::vector<TrapPtr>& get_trap_info_ref() const;

    void set_calendar_days(const std::map<int, CalendarDay>& new_calendar_days);
    std::map<int, CalendarDay>& get_calendar_days_ref();

    void set_starting_locations(const StartingLocationMap& new_starting_locations);
    StartingLocationMap get_starting_locations() const;

    CreaturePtr get_current_player() const;
    ternary get_winner() const;

    void create_new_world(CreaturePtr creature, const StartingLocation& sl);
    void go(); // main game loop
    void stop_playing(CreaturePtr creature, const bool show_quit_actions, const bool delete_savefile); // end the game
    bool should_keep_playing() const; // Check to see if the "game over" flag's been set.
    void set_check_scores(const bool new_check_scores);
    bool should_check_scores() const;

    // Update the physical display
    void update_display();
    void update_display(CreaturePtr creature, MapPtr map, MapPtr fov_sub_map, const bool reloaded_game);

    // Additional operations will eventually be needed to do many
    // worlds and rebirth.
    
    ActionManager& get_action_manager_ref();

    ActionCoordinator& get_action_coordinator_ref();

    DeityActionManager& get_deity_action_manager_ref();

    ScriptEngine& get_script_engine_ref();

    Mortuary& get_mortuary_ref();

    Quests& get_quests_ref();

    void set_sid_ini_filename(const std::string& new_sid_ini_filename);
    std::string get_sid_ini_filename() const;

    void set_scripts(const std::map<std::string, std::string>& new_scripts);
    std::string get_script(const std::string& script_name);
    std::map<std::string, std::string> get_scripts() const;

    World* get_current_world();

    LoadedMapDetails& get_loaded_map_details_ref();

    double get_total_elapsed_game_time(const std::chrono::system_clock::time_point& current_time) const;

    void set_game_start_time(const std::chrono::system_clock::time_point& new_start_time);
    std::chrono::system_clock::time_point get_game_start_time() const;

    void process_elapsed_time(const int seconds);

    void set_current_loaded_savefile(const std::string& current_loaded_savefile);
    std::string get_current_loaded_savefile() const;

    void set_count_score(const bool new_count_score);
    bool get_count_score() const;
    bool should_count_score() const;

    void set_spritesheets(const std::map<std::string, std::pair<std::string, std::unordered_map<std::string, Coordinate>>>& new_spritesheets);
    std::map<std::string, std::pair<std::string, std::unordered_map<std::string, Coordinate>>> get_spritesheets() const;

    virtual void run_map_scripts();

    // Set the map to be used as the current for the game's computational purposes.
    void set_current_map(MapPtr map);

    // SHOULD ONLY BE SET BY UNIT TESTS THAT NEED A TEMPORARY WORLD
    void set_current_world(WorldPtr world);

    void update_player_dates();

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  private:
    friend class ShadowOfTheWyrmEngine;
    friend class BlindedStatusEffect;
    friend class CreatureDeathManager;
    friend class PlayerDeathManager;
    friend class MovementAction;
    friend class DateTimeWeatherAction;
    friend class ItemManager;
    friend class CommandProcessor;
    friend class EquipmentCommandProcessor;
    friend class InventoryCommandProcessor;
    friend class TileSelectionCommandProcessor;
    friend class SeasonsTimeObserver;
    friend class TileSelectionAction;
    friend class ShadowOfTheWyrmEngine;
    friend class GameUtils;
    friend class SW_Engine_Game; // unit testing

    Game();
    Game(const Game& game) = delete;
    bool operator=(const Game& game) = delete;
   ~Game();

    // Game commands - protected, so they should only be called by ShadowOfTheWyrmEngine
    // or CommandProcessor.
    ActionCost process_action_for_creature(CreaturePtr current_creature, MapPtr current_map, const bool reloaded_game);

    // Re-gets the map, and restarts the game loop
    void reload_map();
    
    void detect_creatures_if_necessary(CreaturePtr player, const std::string& original_map_id);
        
    // Process the elapsed time: update the calendar, and notify any time observers.
    void process_elapsed_time(Calendar& calendar, const ActionCost& next_action_cost);

    // Update the scorefile if necessary, when leaving the game.
    void update_score_file_if_necessary(CreaturePtr creature);

    // Save the game after an exception.
    void exit_on_exception(CreaturePtr player);
    void panic_save(CreaturePtr player);
    
    bool keep_playing;
    bool reload_game_loop;
    bool check_scores;

    // The races, classes, and items are not the actual in-game items;
    // they're the template upon which the in-game items are built.
    bool requires_redraw;
    Settings settings;
    DisplayPtr display;
    SoundPtr sound;
    MapRegistry map_registry;
    std::map<std::pair<std::string, std::string>, std::string> sound_effects;
    Music music;
    DeityMap deities;
    RaceMap races;
    ClassMap classes;
    CreatureMap creatures;
    SpellMap spells;
    CreatureGenerationValuesMap creature_generation_values;
    GenerationValuesMap item_generation_values;
    ItemMap items;
    FeatureMap configurable_features;

    // At some point in the future, you're going to look at this and ask,
    // hey, I separated symbol details from tiles and put into the game 
    // class to save space, why not do the same with creatures?
    //
    // To save you another half-hour of your life, it's because there's
    // scripting support for dynamically manipulating a creature's symbol
    // and colour, for things like jellyfish, shapeshifters, etc.
    //
    // Note that there are no shapeshifters, I'm just saying this to try
    // to persuade you not to try this, again.
    std::vector<DisplayTile> tile_info;
    std::vector<TrapPtr> trap_info;
    std::map<int, CalendarDay> calendar_days;
    StartingLocationMap starting_locations;

    WorldPtr world;

    // The currently-loaded map's ID, used to look up the map in the registry.
    std::string current_map_id;

    // The action manager
    ActionManager actions;

    // The deity action manager - monitors certain key actions, and updates
    // piety based on whether a creature's deity likes that action or not.
    DeityActionManager deity_actions;
    
    // The action coordinator, used to keep track of action order and timing costs.
    ActionCoordinator ac;
    
    // The time keeper, used to handle notifications for HP regeneration, status effects wearing off, etc.
    WorldTimeKeeper time_keeper;

    // Used to execute quests and other scripts
    ScriptEngine script_engine;

    // Keep track of the total number of kills over all creatures ever generated
    // in this game.
    Mortuary mortuary;

    // Keep track of all the active and completed quests.  There is only one
    // instance of this data structure, so it is assumed that it is always
    // being applied to the player.
    Quests quests;

    // The name of the sid ini file (e.g., "shadowofthewyrmtext_en.ini").  This
    // doesn't need to be persisted - it will be loaded each time the
    // program runs.
    std::string sid_ini_filename;
    
    // Scripts to be run at particular times: after character creation, etc.
    std::map<std::string, std::string> scripts;

    // The command factory and keyboard map
    CommandFactoryPtr game_command_factory;
    KeyboardCommandMapPtr game_kb_command_map;

    // Keep track of whether a full map redraw is needed.  The map is typically
    // only partially drawn to squeeze out some more performance, and allow more
    // processing after the player's turn.
    LoadedMapDetails loaded_map_details;

    // The currently loaded savefile.  Tracked at the game level so that it can
    // be delete after death or quitting.
    std::string current_loaded_savefile;

    // Any spritesheets and references associated with the configuration.
    std::map<std::string, std::pair<std::string, std::unordered_map<std::string, Coordinate>>> spritesheets;

    // Should this game create a score at the end?  Generally yes, unless
    // the Lua console was used with a particular setting in place.
    bool count_score;

    // Total seconds played
    double total_seconds_played;

    // The time at which the game was started.
    std::chrono::system_clock::time_point game_start_time;

    // Is the game currently loading/input blocked?
    bool is_loading;

  private:
    ClassIdentifier internal_class_identifier() const override;
};



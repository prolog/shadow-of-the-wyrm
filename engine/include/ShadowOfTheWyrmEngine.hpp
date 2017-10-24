#pragma once
#include "CharacterCreationDetails.hpp"
#include "Controller.hpp"
#include "Display.hpp"
#include "Settings.hpp"

class Creature;

enum struct EngineStateEnum
{
  ENGINE_STATE_START_NEW_GAME = 0,
  ENGINE_STATE_START_NEW_GAME_RANDOM = 1,
  ENGINE_STATE_SHOW_HIGH_SCORES = 2,
  ENGINE_STATE_LOAD_GAME = 3,
  ENGINE_STATE_STOP = 4
};

class EngineStateManager
{
  public:
    EngineStateManager();

    void set_state(const EngineStateEnum new_state);
    EngineStateEnum get_state() const;

    bool start_new_game() const;
    bool start_new_game_random() const;
    bool show_high_scores() const;
    bool load_existing_game() const;
    bool exit() const;

  protected:
    EngineStateEnum current_state;
};

// Game flow functions - used to branch into New, Load, Exit, etc.
using GameOptionMap = std::map<std::string, EngineStateEnum>;

class ShadowOfTheWyrmEngine
{
  public:    
    ShadowOfTheWyrmEngine();
 
    void start(const Settings& settings);

    void set_controller(ControllerPtr new_controller);
    void set_display(DisplayPtr new_display);

  protected:
    // Allow the map tester class to load up all the items and creatures
    #ifdef MAP_TESTER
    friend int main(int argc, char** argv);
    #endif
    
    void setup_display(const Settings& settings);
    void setup_game();
    void setup_player_and_world();
    void setup_autopickup_settings(std::shared_ptr<Creature> player);

    void initialize_game_option_map();
    void initialize_game_flow_map();

    bool process_game_option(const std::string& game_option);
    bool process_new_game();
    bool process_new_game_random();
    bool process_name_and_start(const CharacterCreationDetails& ccd);
    bool process_show_high_scores();
    bool process_load_game();
    bool process_exit_game();

    bool is_new_game_allowed();
 
    void run_map_scripts();

    EngineStateManager state_manager;
    ControllerPtr controller;
    DisplayPtr display;
    GameOptionMap game_option_map;
    std::map<EngineStateEnum, bool (ShadowOfTheWyrmEngine::*)(void)> game_flow_functions;
};

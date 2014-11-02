#pragma once
#include "Controller.hpp"
#include "Display.hpp"
#include "Settings.hpp"

enum EngineStateEnum
{
  ENGINE_STATE_START_NEW_GAME = 0,
  ENGINE_STATE_LOAD_GAME = 1,
  ENGINE_STATE_STOP = 2
};

class EngineStateManager
{
  public:
    EngineStateManager();

    void set_state(const EngineStateEnum new_state);
    EngineStateEnum get_state() const;

    bool start_new_game() const;
    bool load_existing_game() const;
    bool exit() const;

  protected:
    EngineStateEnum current_state;
};

// Game flow functions - used to branch into New, Load, Exit, etc.
typedef std::map<std::string, EngineStateEnum> GameOptionMap;

class SavageLandsEngine
{
  public:    
    SavageLandsEngine();
 
    void start();

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

    void initialize_game_option_map();
    void initialize_game_flow_map();

    bool process_game_option(const std::string& game_option);
    bool process_new_game();
    bool process_load_game();
    bool process_exit_game();
    
    EngineStateManager state_manager;
    ControllerPtr controller;
    DisplayPtr display;
    GameOptionMap game_option_map;
    std::map<EngineStateEnum, bool (SavageLandsEngine::*)(void)> game_flow_functions;
};

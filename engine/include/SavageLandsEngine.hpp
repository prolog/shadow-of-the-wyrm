#pragma once
#include "Controller.hpp"
#include "Display.hpp"

enum EngineStateEnum
{
  ENGINE_STATE_START = 0,
  ENGINE_STATE_RUNNING = 1,
  ENGINE_STATE_STOP = 2
};

class EngineStateManager
{
  public:
    EngineStateManager();
    bool continue_execution() const;

  protected:
    EngineStateEnum current_state;
};

class SavageLandsEngine
{
  public:
    SavageLandsEngine();
    ~SavageLandsEngine();

    void start();

    void set_controller(ControllerPtr new_controller);
    void set_display(DisplayPtr new_display);

  protected:
    EngineStateManager state_manager;
    ControllerPtr controller;
    DisplayPtr display;
};

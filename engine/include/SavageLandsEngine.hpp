#pragma once
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
    void set_display(DisplayPtr new_display);

  protected:
    EngineStateManager state_manager;
    DisplayPtr display;
};

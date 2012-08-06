#pragma once
#include "KeyboardCommandMap.hpp"

class TileSelectionKeyboardCommandMap : public KeyboardCommandMap
{
  public:
    TileSelectionKeyboardCommandMap();
    virtual ~TileSelectionKeyboardCommandMap();

    // Fail silently
    virtual void command_not_found(const std::string& keyboard_input);

  protected:
    // Initialize the keys used to move around and select tiles
    virtual void initialize_command_mapping();
};

#pragma once
#include "KeyboardCommandMap.hpp"

class TileSelectionKeyboardCommandMap : public KeyboardCommandMap
{
  public:
    TileSelectionKeyboardCommandMap();
    virtual ~TileSelectionKeyboardCommandMap();

    // Fail silently
    virtual void command_not_found(const std::string& keyboard_input);

    // serialize/deserialize taken care of by KeyboardCommandMap

    virtual KeyboardCommandMap* clone();

  protected:
    // Initialize the keys used to move around and select tiles
    virtual void initialize_command_mapping();

  private:
    ClassIdentifier internal_class_identifier() const;
};

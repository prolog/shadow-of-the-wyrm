#pragma once
#include "KeyboardCommandMap.hpp"

class EquipmentKeyboardCommandMap : public KeyboardCommandMap
{
  public:
    EquipmentKeyboardCommandMap();
    virtual ~EquipmentKeyboardCommandMap();

    // Fail silently.
    virtual void command_not_found(const std::string& keyboard_input);
  
  protected:
    // The equipment keys mean different things than the parent class's
    // map!
    virtual void initialize_command_mapping();
};

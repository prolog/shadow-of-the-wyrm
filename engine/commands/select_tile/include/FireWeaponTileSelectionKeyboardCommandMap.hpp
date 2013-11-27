#pragma once
#include "TileSelectionKeyboardCommandMap.hpp"

class FireWeaponTileSelectionKeyboardCommandMap : public TileSelectionKeyboardCommandMap
{
  public:
    FireWeaponTileSelectionKeyboardCommandMap();
    virtual ~FireWeaponTileSelectionKeyboardCommandMap();

    // Fail silently
    virtual void command_not_found(const std::string& keyboard_input) override;

  protected:
    // Include everything from the parent class, but also a 
    // "f"ire keybinding.
    virtual void initialize_command_mapping() override;
};

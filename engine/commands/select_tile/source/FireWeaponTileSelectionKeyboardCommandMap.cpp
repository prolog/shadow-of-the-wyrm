#ifdef _MSC_VER
#include <curses.h>
#else
#include <ncurses.h>
#endif
#include "Conversion.hpp"
#include "TileSelectionCommandKeys.hpp"
#include "FireWeaponTileSelectionKeyboardCommandMap.hpp"

using std::string;

FireWeaponTileSelectionKeyboardCommandMap::FireWeaponTileSelectionKeyboardCommandMap()
{
}

FireWeaponTileSelectionKeyboardCommandMap::~FireWeaponTileSelectionKeyboardCommandMap()
{
}

void FireWeaponTileSelectionKeyboardCommandMap::command_not_found(const string& keyboard_input)
{
  if (!keyboard_input.empty())
  {
    // Do nothing for now!
  }
}

void FireWeaponTileSelectionKeyboardCommandMap::initialize_command_mapping()
{
  TileSelectionKeyboardCommandMap::initialize_command_mapping();

  // fire
  command_mapping.insert(make_pair(Integer::to_string('f'), TileSelectionCommandKeys::TARGET_TILE));
}


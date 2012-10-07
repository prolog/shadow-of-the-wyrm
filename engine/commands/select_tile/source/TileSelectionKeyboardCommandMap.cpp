#ifdef _MSC_VER
#include <curses.h>
#else
#include <ncurses.h>
#endif

#include "Conversion.hpp"
#include "TileSelectionCommandKeys.hpp"
#include "TileSelectionKeyboardCommandMap.hpp"

using std::string;

TileSelectionKeyboardCommandMap::TileSelectionKeyboardCommandMap()
{
}

TileSelectionKeyboardCommandMap::~TileSelectionKeyboardCommandMap()
{
}

void TileSelectionKeyboardCommandMap::command_not_found(const string& keyboard_input)
{
  if (!keyboard_input.empty())
  {
    // Do nothing for now!
  }
}

void TileSelectionKeyboardCommandMap::initialize_command_mapping()
{
  command_mapping.clear();
  
  // Cancel
  command_mapping.insert(make_pair(Integer::to_string('z'), TileSelectionCommandKeys::CANCEL_TILE_SELECTION));
  command_mapping.insert(make_pair(Integer::to_string('Z'), TileSelectionCommandKeys::CANCEL_TILE_SELECTION));

  // Arrow keys
  command_mapping.insert(make_pair(Integer::to_string(KEY_UP), TileSelectionCommandKeys::CURSOR_MOVE_NORTH));
  command_mapping.insert(make_pair(Integer::to_string(KEY_DOWN), TileSelectionCommandKeys::CURSOR_MOVE_SOUTH));
  command_mapping.insert(make_pair(Integer::to_string(KEY_LEFT), TileSelectionCommandKeys::CURSOR_MOVE_WEST));
  command_mapping.insert(make_pair(Integer::to_string(KEY_RIGHT), TileSelectionCommandKeys::CURSOR_MOVE_EAST));

  // Number keys
  command_mapping.insert(make_pair(Integer::to_string('1'), TileSelectionCommandKeys::CURSOR_MOVE_SOUTHWEST));
  command_mapping.insert(make_pair(Integer::to_string('2'), TileSelectionCommandKeys::CURSOR_MOVE_SOUTH));
  command_mapping.insert(make_pair(Integer::to_string('3'), TileSelectionCommandKeys::CURSOR_MOVE_SOUTHEAST));
  command_mapping.insert(make_pair(Integer::to_string('4'), TileSelectionCommandKeys::CURSOR_MOVE_WEST));
  command_mapping.insert(make_pair(Integer::to_string('6'), TileSelectionCommandKeys::CURSOR_MOVE_EAST));
  command_mapping.insert(make_pair(Integer::to_string('7'), TileSelectionCommandKeys::CURSOR_MOVE_NORTHWEST));
  command_mapping.insert(make_pair(Integer::to_string('8'), TileSelectionCommandKeys::CURSOR_MOVE_NORTH));
  command_mapping.insert(make_pair(Integer::to_string('9'), TileSelectionCommandKeys::CURSOR_MOVE_NORTHEAST));

  // vi keys
  command_mapping.insert(make_pair(Integer::to_string('y'), TileSelectionCommandKeys::CURSOR_MOVE_NORTHWEST));
  command_mapping.insert(make_pair(Integer::to_string('u'), TileSelectionCommandKeys::CURSOR_MOVE_NORTHEAST));
  command_mapping.insert(make_pair(Integer::to_string('h'), TileSelectionCommandKeys::CURSOR_MOVE_WEST));
  command_mapping.insert(make_pair(Integer::to_string('j'), TileSelectionCommandKeys::CURSOR_MOVE_SOUTH));
  command_mapping.insert(make_pair(Integer::to_string('k'), TileSelectionCommandKeys::CURSOR_MOVE_NORTH));
  command_mapping.insert(make_pair(Integer::to_string('l'), TileSelectionCommandKeys::CURSOR_MOVE_EAST));
  command_mapping.insert(make_pair(Integer::to_string('b'), TileSelectionCommandKeys::CURSOR_MOVE_SOUTHWEST));
  command_mapping.insert(make_pair(Integer::to_string('n'), TileSelectionCommandKeys::CURSOR_MOVE_SOUTHEAST));
}

KeyboardCommandMap* TileSelectionKeyboardCommandMap::clone()
{
  return new TileSelectionKeyboardCommandMap(*this);
}

ClassIdentifier TileSelectionKeyboardCommandMap::internal_class_identifier() const
{
  return CLASS_ID_TILE_SELECTION_KEYBOARD_COMMAND_MAP;
}
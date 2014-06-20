#ifdef _MSC_VER
#include <curses.h>
#else
#include <ncurses.h>
#endif

#include "Conversion.hpp"
#include "CommandKeys.hpp"
#include "TileSelectionCommandKeys.hpp"
#include "TileSelectionKeyboardCommandMap.hpp"

using namespace std;

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
  command_mapping = KeyboardCommandMappingMap{{Integer::to_string('z'), TileSelectionCommandKeys::CANCEL_TILE_SELECTION},
                                              {Integer::to_string('Z'), TileSelectionCommandKeys::CANCEL_TILE_SELECTION},
                                              {Integer::to_string(KEY_UP), TileSelectionCommandKeys::CURSOR_MOVE_NORTH},
                                              {Integer::to_string(KEY_DOWN), TileSelectionCommandKeys::CURSOR_MOVE_SOUTH},
                                              {Integer::to_string(KEY_LEFT), TileSelectionCommandKeys::CURSOR_MOVE_WEST},
                                              {Integer::to_string(KEY_RIGHT), TileSelectionCommandKeys::CURSOR_MOVE_EAST},
                                              {Integer::to_string('1'), TileSelectionCommandKeys::CURSOR_MOVE_SOUTHWEST},
                                              {Integer::to_string('2'), TileSelectionCommandKeys::CURSOR_MOVE_SOUTH},
                                              {Integer::to_string('3'), TileSelectionCommandKeys::CURSOR_MOVE_SOUTHEAST},
                                              {Integer::to_string('4'), TileSelectionCommandKeys::CURSOR_MOVE_WEST},
                                              {Integer::to_string('6'), TileSelectionCommandKeys::CURSOR_MOVE_EAST},
                                              {Integer::to_string('7'), TileSelectionCommandKeys::CURSOR_MOVE_NORTHWEST},
                                              {Integer::to_string('8'), TileSelectionCommandKeys::CURSOR_MOVE_NORTH},
                                              {Integer::to_string('9'), TileSelectionCommandKeys::CURSOR_MOVE_NORTHEAST},
                                              {Integer::to_string('y'), TileSelectionCommandKeys::CURSOR_MOVE_NORTHWEST},
                                              {Integer::to_string('u'), TileSelectionCommandKeys::CURSOR_MOVE_NORTHEAST},
                                              {Integer::to_string('h'), TileSelectionCommandKeys::CURSOR_MOVE_WEST},
                                              {Integer::to_string('j'), TileSelectionCommandKeys::CURSOR_MOVE_SOUTH},
                                              {Integer::to_string('k'), TileSelectionCommandKeys::CURSOR_MOVE_NORTH},
                                              {Integer::to_string('l'), TileSelectionCommandKeys::CURSOR_MOVE_EAST},
                                              {Integer::to_string('b'), TileSelectionCommandKeys::CURSOR_MOVE_SOUTHWEST},
                                              {Integer::to_string('n'), TileSelectionCommandKeys::CURSOR_MOVE_SOUTHEAST},
                                              {Integer::to_string('+'), TileSelectionCommandKeys::TARGET_NEXT_CREATURE},
                                              {Integer::to_string('-'), TileSelectionCommandKeys::TARGET_PREV_CREATURE},
                                              {Integer::to_string('B'), CommandKeys::BESTIARY}};
}

KeyboardCommandMap* TileSelectionKeyboardCommandMap::clone()
{
  return new TileSelectionKeyboardCommandMap(*this);
}

string TileSelectionKeyboardCommandMap::get_settings_prefix() const
{
  return "key_til_";
}

ClassIdentifier TileSelectionKeyboardCommandMap::internal_class_identifier() const
{
  return CLASS_ID_TILE_SELECTION_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/TileSelectionKeyboardCommandMap_test.cpp"
#endif


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

vector<string> TileSelectionKeyboardCommandMap::get_remappable_commands() const
{
  return
  {
    TileSelectionCommandKeys::CURSOR_MOVE_SOUTHWEST, TileSelectionCommandKeys::CURSOR_MOVE_SOUTH,
    TileSelectionCommandKeys::CURSOR_MOVE_SOUTHEAST, TileSelectionCommandKeys::CURSOR_MOVE_WEST,
    TileSelectionCommandKeys::CURSOR_MOVE_EAST, TileSelectionCommandKeys::CURSOR_MOVE_NORTHWEST,
    TileSelectionCommandKeys::CURSOR_MOVE_NORTH, TileSelectionCommandKeys::CURSOR_MOVE_EAST,
    CommandKeys::BESTIARY
  };
}
void TileSelectionKeyboardCommandMap::initialize_command_mapping(const Settings& settings)
{
  command_mapping.clear();

  // Non-remappable commands
  command_mapping = KeyboardCommandMappingMap
  { { Integer::to_string('z'), TileSelectionCommandKeys::CANCEL_TILE_SELECTION },
  { Integer::to_string('Z'), TileSelectionCommandKeys::CANCEL_TILE_SELECTION },
  { Integer::to_string('+'), TileSelectionCommandKeys::TARGET_NEXT_CREATURE },
  { Integer::to_string('-'), TileSelectionCommandKeys::TARGET_PREV_CREATURE } };

  initialize_special_key_mappings();
  vector<string> remappable_commands = get_remappable_commands();

  parse_keybindings(settings, remappable_commands);
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
  return ClassIdentifier::CLASS_ID_TILE_SELECTION_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/TileSelectionKeyboardCommandMap_test.cpp"
#endif


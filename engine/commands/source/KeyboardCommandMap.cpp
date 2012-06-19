#include <ncurses.h>
#include "CommandKeys.hpp"
#include "Conversion.hpp"
#include "KeyboardCommandMap.hpp"
#include "Log.hpp"
#include "MessageManager.hpp"
#include "StringConstants.hpp"

using namespace std;

KeyboardCommandMap::KeyboardCommandMap()
{
}

KeyboardCommandMap::~KeyboardCommandMap()
{
}

// Returns the internal command name, which can be passed to the
// CommandFactory to get the appropriate CommandPtr.
string KeyboardCommandMap::get_command_type(const string& keyboard_input)
{
  string mapped_command;

  if (command_mapping.empty())
  {
    initialize_command_mapping();
  }

  map<string, string>::iterator m_it = command_mapping.find(keyboard_input);

  if (m_it != command_mapping.end())
  {
    mapped_command = m_it->second;
  }
  else
  {
    command_not_found(keyboard_input);
  }

  return mapped_command;
}

void KeyboardCommandMap::command_not_found(const string& keyboard_input)
{
  // JCD FIXME: Does the wrong thing for function keys, etc.  Maybe use the String::clean function?
  string keyboard_input_as_character = Char::to_string(String::to_int(keyboard_input));
  MessageManager* manager = MessageManager::instance();
//  manager->clear_if_necessary();
  manager->add_new_message(TextMessages::get_action_not_found_message(keyboard_input_as_character));
  manager->send(false /* Don't halt */, true /* Reset the cursor on the player */);

  Log* log = Log::instance();
  log->debug("Could not find mapped command for input: " + keyboard_input);
}

void KeyboardCommandMap::initialize_command_mapping()
{
  command_mapping.clear();

  command_mapping.insert(make_pair(Integer::to_string('Q'), CommandKeys::QUIT));
  command_mapping.insert(make_pair(Integer::to_string('v'), CommandKeys::VERSION));
  command_mapping.insert(make_pair(Integer::to_string('T'), CommandKeys::GAME_DATE_TIME));
  command_mapping.insert(make_pair(Integer::to_string('s'), CommandKeys::SEARCH));
  command_mapping.insert(make_pair(Integer::to_string('5'), CommandKeys::SEARCH));
  command_mapping.insert(make_pair(Integer::to_string('1'), CommandKeys::MOVE_SOUTHWEST));
  command_mapping.insert(make_pair(Integer::to_string('2'), CommandKeys::MOVE_SOUTH));
  command_mapping.insert(make_pair(Integer::to_string('3'), CommandKeys::MOVE_SOUTHEAST));
  command_mapping.insert(make_pair(Integer::to_string(8) /* Backspace */, CommandKeys::MOVE_WEST));
  command_mapping.insert(make_pair(Integer::to_string('4'), CommandKeys::MOVE_WEST));
  command_mapping.insert(make_pair(Integer::to_string(32) /* Space */, CommandKeys::MOVE_EAST));
  command_mapping.insert(make_pair(Integer::to_string('6'), CommandKeys::MOVE_EAST));
  command_mapping.insert(make_pair(Integer::to_string('7'), CommandKeys::MOVE_NORTHWEST));
  command_mapping.insert(make_pair(Integer::to_string('8'), CommandKeys::MOVE_NORTH));
  command_mapping.insert(make_pair(Integer::to_string('9'), CommandKeys::MOVE_NORTHEAST));
  // NCurses-specific movement keys
  command_mapping.insert(make_pair(Integer::to_string(KEY_UP), CommandKeys::MOVE_NORTH));
  command_mapping.insert(make_pair(Integer::to_string(KEY_DOWN), CommandKeys::MOVE_SOUTH));
  command_mapping.insert(make_pair(Integer::to_string(KEY_RIGHT), CommandKeys::MOVE_EAST));
  command_mapping.insert(make_pair(Integer::to_string(KEY_LEFT), CommandKeys::MOVE_WEST));
  // End of NCurses-specific movement keys
  command_mapping.insert(make_pair(Integer::to_string('<'), CommandKeys::MOVE_UP));
  command_mapping.insert(make_pair(Integer::to_string('>'), CommandKeys::MOVE_DOWN));
  command_mapping.insert(make_pair(Integer::to_string(','), CommandKeys::PICK_UP_ITEM));
  command_mapping.insert(make_pair(Integer::to_string('d'), CommandKeys::DROP_ITEM));
  command_mapping.insert(make_pair(Integer::to_string('i'), CommandKeys::INVENTORY));
  command_mapping.insert(make_pair(Integer::to_string('@'), CommandKeys::CHAR_DUMP));
}

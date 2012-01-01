#include <ncurses.h>
#include "CommandKeys.hpp"
#include "Conversion.hpp"
#include "KeyboardCommandMap.hpp"
#include "Log.hpp"

using namespace std;

std::map<std::string, std::string> KeyboardCommandMap::command_mapping;

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
    Log* log = Log::instance();
    log->debug("Could not find mapped command for input: " + keyboard_input);
  }

  return mapped_command;
}

void KeyboardCommandMap::initialize_command_mapping()
{
  command_mapping.clear();

  command_mapping.insert(make_pair(Integer::to_string('Q'), CommandKeys::QUIT));
  command_mapping.insert(make_pair(Integer::to_string('v'), CommandKeys::VERSION));
  command_mapping.insert(make_pair(Integer::to_string('s'), CommandKeys::SEARCH));
  command_mapping.insert(make_pair(Integer::to_string('5'), CommandKeys::SEARCH));
  command_mapping.insert(make_pair(Integer::to_string('1'), CommandKeys::MOVE_SOUTHWEST));
  command_mapping.insert(make_pair(Integer::to_string('2'), CommandKeys::MOVE_SOUTH));
  command_mapping.insert(make_pair(Integer::to_string('3'), CommandKeys::MOVE_SOUTHEAST));
  command_mapping.insert(make_pair(Integer::to_string('4'), CommandKeys::MOVE_WEST));
  command_mapping.insert(make_pair(Integer::to_string('6'), CommandKeys::MOVE_EAST));
  command_mapping.insert(make_pair(Integer::to_string('7'), CommandKeys::MOVE_NORTHWEST));
  command_mapping.insert(make_pair(Integer::to_string('8'), CommandKeys::MOVE_NORTH));
  command_mapping.insert(make_pair(Integer::to_string('9'), CommandKeys::MOVE_NORTHEAST));
  // NCurses-specific movement keys
  // JCD FIXME: These aren't working, yet.
  command_mapping.insert(make_pair(Integer::to_string(KEY_UP), CommandKeys::MOVE_NORTH));
  command_mapping.insert(make_pair(Integer::to_string(KEY_DOWN), CommandKeys::MOVE_SOUTH));
  command_mapping.insert(make_pair(Integer::to_string(KEY_RIGHT), CommandKeys::MOVE_EAST));
  command_mapping.insert(make_pair(Integer::to_string(KEY_LEFT), CommandKeys::MOVE_WEST));
  // End of NCurses-specific movement keys
}

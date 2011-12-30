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

  command_mapping.insert(make_pair("Q", "QUIT"));
  command_mapping.insert(make_pair("v", "VERSION"));
}

#ifdef _MSC_VER
#include <curses.h>
#else
#include <ncurses.h>
#endif
#include "CommandKeys.hpp"
#include "Conversion.hpp"
#include "KeyboardCommandMap.hpp"
#include "Log.hpp"
#include "MessageManagerFactory.hpp"
#include "Serialize.hpp"
#include "TextMessages.hpp"

using namespace std;

KeyboardCommandMap::KeyboardCommandMap()
{
}

KeyboardCommandMap::~KeyboardCommandMap()
{
}

bool KeyboardCommandMap::operator==(const KeyboardCommandMap& kcm) const
{
  bool result = true;

  result = (command_mapping == kcm.command_mapping);

  return result;
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

KeyboardCommandMappingMap KeyboardCommandMap::get_internal_map()
{
  if (command_mapping.empty())
  {
    initialize_command_mapping();
  }

  return command_mapping;
}

void KeyboardCommandMap::command_not_found(const string& keyboard_input)
{
  // JCD FIXME: Does the wrong thing for function keys, etc.  Maybe use the String::clean function?
  string keyboard_input_as_character = Char::to_string(String::to_int(keyboard_input));
  IMessageManager& manager = MessageManagerFactory::instance();
  manager.add_new_message(TextMessages::get_action_not_found_message(keyboard_input_as_character));
  manager.send(false /* Don't halt */, true /* Reset the cursor on the player */);

  Log::instance().debug("Could not find mapped command for input: " + keyboard_input);
}

void KeyboardCommandMap::initialize_command_mapping()
{
  command_mapping.clear();

  // MSVC bombs when I try to convert this to an initializer list. :(
  command_mapping.insert(make_pair(Integer::to_string('Q'), CommandKeys::QUIT));
  command_mapping.insert(make_pair(Integer::to_string('V'), CommandKeys::VERSION));
  command_mapping.insert(make_pair(Integer::to_string('T'), CommandKeys::GAME_DATE_TIME));
  command_mapping.insert(make_pair(Integer::to_string('s'), CommandKeys::SEARCH));
  command_mapping.insert(make_pair(Integer::to_string('5'), CommandKeys::SEARCH));
  command_mapping.insert(make_pair(Integer::to_string('.'), CommandKeys::SEARCH));
  command_mapping.insert(make_pair(Integer::to_string('1'), CommandKeys::MOVE_SOUTHWEST));
  command_mapping.insert(make_pair(Integer::to_string('2'), CommandKeys::MOVE_SOUTH));
  command_mapping.insert(make_pair(Integer::to_string('3'), CommandKeys::MOVE_SOUTHEAST));
  command_mapping.insert(make_pair(Integer::to_string('4'), CommandKeys::MOVE_WEST));
  command_mapping.insert(make_pair(Integer::to_string('6'), CommandKeys::MOVE_EAST));
  command_mapping.insert(make_pair(Integer::to_string('7'), CommandKeys::MOVE_NORTHWEST));
  command_mapping.insert(make_pair(Integer::to_string('8'), CommandKeys::MOVE_NORTH));
  command_mapping.insert(make_pair(Integer::to_string('9'), CommandKeys::MOVE_NORTHEAST));
  // Curses-specific movement keys
  command_mapping.insert(make_pair(Integer::to_string(KEY_UP), CommandKeys::MOVE_NORTH));
  command_mapping.insert(make_pair(Integer::to_string(KEY_DOWN), CommandKeys::MOVE_SOUTH));
  command_mapping.insert(make_pair(Integer::to_string(KEY_RIGHT), CommandKeys::MOVE_EAST));
  command_mapping.insert(make_pair(Integer::to_string(KEY_LEFT), CommandKeys::MOVE_WEST));
  // vi movement keys
  command_mapping.insert(make_pair(Integer::to_string('b'), CommandKeys::MOVE_SOUTHWEST));
  command_mapping.insert(make_pair(Integer::to_string('j'), CommandKeys::MOVE_SOUTH));
  command_mapping.insert(make_pair(Integer::to_string('n'), CommandKeys::MOVE_SOUTHEAST));
  command_mapping.insert(make_pair(Integer::to_string('h'), CommandKeys::MOVE_WEST));
  command_mapping.insert(make_pair(Integer::to_string('l'), CommandKeys::MOVE_EAST));
  command_mapping.insert(make_pair(Integer::to_string('y'), CommandKeys::MOVE_NORTHWEST));
  command_mapping.insert(make_pair(Integer::to_string('k'), CommandKeys::MOVE_NORTH));
  command_mapping.insert(make_pair(Integer::to_string('u'), CommandKeys::MOVE_NORTHEAST));
  // other movement-type commands
  command_mapping.insert(make_pair(Integer::to_string('w'), CommandKeys::AUTOMATIC_MOVEMENT));

  command_mapping.insert(make_pair(Integer::to_string('<'), CommandKeys::MOVE_UP));
  command_mapping.insert(make_pair(Integer::to_string('>'), CommandKeys::MOVE_DOWN));
  command_mapping.insert(make_pair(Integer::to_string(','), CommandKeys::PICK_UP_ITEM));
  command_mapping.insert(make_pair(Integer::to_string('d'), CommandKeys::DROP_ITEM));
  command_mapping.insert(make_pair(Integer::to_string('i'), CommandKeys::INVENTORY));
  command_mapping.insert(make_pair(Integer::to_string('@'), CommandKeys::CHAR_DUMP));
  command_mapping.insert(make_pair(Integer::to_string('_'), CommandKeys::PRAY));
  command_mapping.insert(make_pair(Integer::to_string('W'), CommandKeys::MELEE_WEAPON_INFO));
  command_mapping.insert(make_pair(Integer::to_string('R'), CommandKeys::RANGED_WEAPON_INFO));
  command_mapping.insert(make_pair(Integer::to_string('L'), CommandKeys::SELECT_TILE));
  command_mapping.insert(make_pair(Integer::to_string('f'), CommandKeys::FIRE_MISSILE));
  command_mapping.insert(make_pair(Integer::to_string('D'), CommandKeys::QUAFF)); // need 'q' for quests.
  command_mapping.insert(make_pair(Integer::to_string('r'), CommandKeys::READ));
  command_mapping.insert(make_pair(Integer::to_string('$'), CommandKeys::CHECK_CURRENCY));
  command_mapping.insert(make_pair(Integer::to_string('S'), CommandKeys::SAVE_GAME));
  command_mapping.insert(make_pair(Integer::to_string('e'), CommandKeys::EAT));
  command_mapping.insert(make_pair(Integer::to_string('C'), CommandKeys::CHAT));
  command_mapping.insert(make_pair(Integer::to_string('a'), CommandKeys::APPLY_FEATURE));
  command_mapping.insert(make_pair(Integer::to_string('q'), CommandKeys::QUEST_LIST));
  command_mapping.insert(make_pair(Integer::to_string('z'), CommandKeys::CAST_SPELL));
  command_mapping.insert(make_pair(Integer::to_string('B'), CommandKeys::BESTIARY));
  command_mapping.insert(make_pair(Integer::to_string('v'), CommandKeys::EVOKE));
  
  command_mapping.insert(make_pair(Integer::to_string(KEY_F(1)), CommandKeys::SHOW_RESISTANCES));
  command_mapping.insert(make_pair(Integer::to_string(KEY_F(2)), CommandKeys::SHOW_CONDUCTS));

  // JCD FIXME: When adding Unix support, update this to include whatever
  // debug flag is needed.
  #ifdef _DEBUG
  command_mapping.insert(make_pair(Integer::to_string(KEY_F(11)), CommandKeys::RUN_SCRIPT));
  #endif

  // Function Keys
  command_mapping.insert(make_pair(Integer::to_string(KEY_F(12)), CommandKeys::RELOAD_SCRIPTS_AND_SIDS));
}

// Handle serialization of the keyboard/command-key map.  Any additional values added by subclasses
// will be handled automatically by this function.
bool KeyboardCommandMap::serialize(std::ostream& stream) const
{
  Serialize::write_size_t(stream, command_mapping.size());

  for (const KeyboardCommandMappingMap::value_type& kb_pair : command_mapping)
  {
    string keyboard_keypress = kb_pair.first;
    string command_key = kb_pair.second;

    Serialize::write_string(stream, keyboard_keypress);
    Serialize::write_string(stream, command_key);
  }

  return true;
}

// Handle deserialization of the map.  Any additional values added by the subclasses will be handled
// automatically.
bool KeyboardCommandMap::deserialize(std::istream& stream)
{
  size_t mapping_size;
  Serialize::read_size_t(stream, mapping_size);

  command_mapping.clear();

  for (unsigned int i = 0; i < mapping_size; i++)
  {
    string keyboard_keypress;
    string command_key;

    Serialize::read_string(stream, keyboard_keypress);
    Serialize::read_string(stream, command_key);

    command_mapping.insert(make_pair(keyboard_keypress, command_key));
  }

  return true;
}

KeyboardCommandMap* KeyboardCommandMap::clone()
{
  return new KeyboardCommandMap(*this);
}

ClassIdentifier KeyboardCommandMap::internal_class_identifier() const
{
  return CLASS_ID_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/KeyboardCommandMap_test.cpp"
#endif

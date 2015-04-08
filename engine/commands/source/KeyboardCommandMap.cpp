#ifdef _MSC_VER
#include <curses.h>
#else
#include <ncurses.h>
#endif
#include "CommandKeys.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "KeyboardCommandMap.hpp"
#include "Log.hpp"
#include "MessageManagerFactory.hpp"
#include "Serialize.hpp"
#include "SettingKeybindings.hpp"
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
  Game& game = Game::instance();

  if (command_mapping.empty())
  {
    initialize_command_mapping(game.get_settings_ref());
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
  Game& game = Game::instance();

  if (command_mapping.empty())
  {
    initialize_command_mapping(game.get_settings_ref());
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

  Log::instance().debug("KeyboardCommandMap::command_not_found - could not find mapped command for input: " + keyboard_input);
}

// Initializes the "special key" map, which maps from a string description of the key
// e.g., "KEY_F12", to the int->string conversion of the actual value.
void KeyboardCommandMap::initialize_special_key_mappings()
{
  special_key_mappings.clear();

  special_key_mappings.insert(make_pair("KEY_UP", Integer::to_string(KEY_UP)));
  special_key_mappings.insert(make_pair("KEY_DOWN", Integer::to_string(KEY_DOWN)));
  special_key_mappings.insert(make_pair("KEY_LEFT", Integer::to_string(KEY_LEFT)));
  special_key_mappings.insert(make_pair("KEY_RIGHT", Integer::to_string(KEY_RIGHT)));
  special_key_mappings.insert(make_pair("KEY_F1", Integer::to_string(KEY_F(1))));
  special_key_mappings.insert(make_pair("KEY_F2", Integer::to_string(KEY_F(2))));
  special_key_mappings.insert(make_pair("KEY_F12", Integer::to_string(KEY_F(12))));
}

vector<string> KeyboardCommandMap::get_remappable_commands() const
{
  return 
  { CommandKeys::SEARCH, CommandKeys::MOVE_SOUTHWEST, CommandKeys::MOVE_SOUTH,
  CommandKeys::MOVE_SOUTHEAST, CommandKeys::MOVE_WEST, CommandKeys::MOVE_EAST,
  CommandKeys::MOVE_NORTHWEST, CommandKeys::MOVE_NORTH, CommandKeys::MOVE_NORTHEAST,
  CommandKeys::MOVE_UP, CommandKeys::MOVE_DOWN, CommandKeys::AUTOMATIC_MOVEMENT,
  CommandKeys::QUIT, CommandKeys::SAVE_GAME, CommandKeys::VERSION,
  CommandKeys::GAME_DATE_TIME, CommandKeys::CHAR_DUMP, CommandKeys::MELEE_WEAPON_INFO,
  CommandKeys::RANGED_WEAPON_INFO, CommandKeys::SHOW_CONDUCTS, CommandKeys::SHOW_RESISTANCES,
  CommandKeys::PICK_UP_ITEM, CommandKeys::DROP_ITEM, CommandKeys::INVENTORY,
  CommandKeys::PRAY, CommandKeys::SELECT_TILE, CommandKeys::FIRE_MISSILE,
  CommandKeys::QUAFF, CommandKeys::READ, CommandKeys::CHECK_CURRENCY,
  CommandKeys::EAT, CommandKeys::CHAT, CommandKeys::APPLY_FEATURE,
  CommandKeys::QUEST_LIST, CommandKeys::CAST_SPELL, CommandKeys::BESTIARY,
  CommandKeys::EVOKE, CommandKeys::LATEST_MESSAGES, CommandKeys::KICK,
  CommandKeys::OFFER, CommandKeys::SKIN, CommandKeys::PIETY,
  CommandKeys::EXPERIENCE};
}

void KeyboardCommandMap::parse_keybindings(const Settings& settings, const vector<string>& remappable_commands)
{
  string prefix = get_settings_prefix();

  SettingKeybindings sk;

  // FIXME: These are currently not being picked up.
  // Probably it is because the command processor expects an int -> string
  // instead of just a string...
  for (const auto& remap_cmd : remappable_commands)
  {
    vector<string> keys = sk.get_keybindings(settings.get_setting(prefix + remap_cmd));

    for (const auto& key : keys)
    {
      // If key is length 1, it's a single character.
      if (key.size() == 1)
      {
        command_mapping.insert(make_pair(Integer::to_string(key.at(0)), remap_cmd));
      }
      // Otherwise, it's a special key, like KEY_UP or whatever.
      // We should already have a mapping for these, so look it up.
      else
      {
        auto mapping = special_key_mappings.find(key);

        if (mapping != special_key_mappings.end())
        {
          command_mapping.insert(make_pair(mapping->second, remap_cmd));
        }
      }
    }
  }

}

void KeyboardCommandMap::initialize_command_mapping(const Settings& settings)
{
  command_mapping.clear();

  initialize_special_key_mappings();
  vector<string> remappable_commands = get_remappable_commands();

  parse_keybindings(settings, remappable_commands);

  // Non-remappable commands
  //
  // JCD FIXME: When adding Unix support, update this to include whatever
  // debug flag is needed.
  #ifdef _DEBUG
  command_mapping.insert(make_pair(Integer::to_string(KEY_F(11)), CommandKeys::RUN_SCRIPT));
  #endif
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

string KeyboardCommandMap::get_settings_prefix() const
{
  return "key_";
}

ClassIdentifier KeyboardCommandMap::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/KeyboardCommandMap_test.cpp"
#endif

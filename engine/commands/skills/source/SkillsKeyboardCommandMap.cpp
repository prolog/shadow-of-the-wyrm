#include "curses.hpp"

#include "Conversion.hpp"
#include "CursesConstants.hpp"
#include "Game.hpp"
#include "Setting.hpp"
#include "SkillsCommandKeys.hpp"
#include "SkillsKeyboardCommandMap.hpp"

using namespace std;

SkillsKeyboardCommandMap::SkillsKeyboardCommandMap()
{
}

SkillsKeyboardCommandMap::~SkillsKeyboardCommandMap()
{
}

void SkillsKeyboardCommandMap::command_not_found(const string& keyboard_input)
{
  if (!keyboard_input.empty())
  {
    // Fail silently.
  }
}

// Settings currently does nothing here.
void SkillsKeyboardCommandMap::initialize_command_mapping(const Settings& /*settings*/)
{
  string esc_key;
  esc_key = NC_ESCAPE_KEY;

  command_mapping.clear();
  command_mapping = KeyboardCommandMappingMap{ 
  { std::to_string('1'), SkillsCommandKeys::GENERAL_SKILLS },
  { std::to_string('2'), SkillsCommandKeys::MELEE_WEAPON_SKILLS },
  { std::to_string('3'), SkillsCommandKeys::RANGED_WEAPON_SKILLS },
  { std::to_string('4'), SkillsCommandKeys::MAGIC_SKILLS},
  { std::to_string('z'), SkillsCommandKeys::EXIT_SKILLS },
  { std::to_string('Z'), SkillsCommandKeys::EXIT_SKILLS },
  { std::to_string(NC_ESCAPE_KEY), SkillsCommandKeys::EXIT_SKILLS },
  { esc_key, SkillsCommandKeys::EXIT_SKILLS } };

  bool req_caps = Game::instance().get_settings_ref().get_setting_as_bool(Setting::SKILL_SELECTION_REQUIRE_CAPITALIZATION);

  for (char i = 'a'; i <= 'y'; i++)
  {
    if (req_caps)
    {
      command_mapping.insert(make_pair(std::to_string(toupper(i)), SkillsCommandKeys::SELECT_SKILL));
      command_mapping.insert(make_pair(std::to_string(i), SkillsCommandKeys::SKILL_DESCRIPTION));
    }
    else
    {
      command_mapping.insert(make_pair(std::to_string(i), SkillsCommandKeys::SELECT_SKILL));
      command_mapping.insert(make_pair(std::to_string(toupper(i)), SkillsCommandKeys::SKILL_DESCRIPTION));
    }
  }
}

void SkillsKeyboardCommandMap::initialize_special_key_mappings()
{
}

KeyboardCommandMap* SkillsKeyboardCommandMap::clone()
{
  return new SkillsKeyboardCommandMap(*this);
}

string SkillsKeyboardCommandMap::get_settings_prefix() const
{
  return "key_skills_";
}

ClassIdentifier SkillsKeyboardCommandMap::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILLS_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/SkillsKeyboardCommandMap_test.cpp"
#endif

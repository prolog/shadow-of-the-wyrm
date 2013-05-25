#include "MessageManager.hpp"
#include "SpellbookReadStrategy.hpp"
#include "Spellbook.hpp"
#include "SpellcastingTextKeys.hpp"
#include "StringTable.hpp"

ActionCostValue SpellbookReadStrategy::read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable)
{
  ActionCostValue acv = 0;

  if (creature && readable)
  {
    SpellbookPtr spellbook = boost::dynamic_pointer_cast<Spellbook>(readable);

    if (spellbook)
    {
      if (check_magic_skill(creature))
      {
      }
    }

    acv = get_action_cost_value();
  }

  return acv;
}

ActionCostValue SpellbookReadStrategy::get_action_cost_value() const
{
  return 1;
}

// Check to see if the creature can actually read the runes on the page.
bool SpellbookReadStrategy::check_magic_skill(CreaturePtr creature)
{
  bool has_magic_skill = true;

  SkillPtr magic_skill = creature->get_skills().get_skill(SKILL_GENERAL_MAGIC);

  if (magic_skill->get_value() <= 0)
  {
    if (creature->get_is_player())
    {
      add_no_magic_skill_message();
      has_magic_skill = false;
    }
  }

  return has_magic_skill;
}

void SpellbookReadStrategy::add_no_magic_skill_message()
{
  MessageManager& manager = MessageManager::instance();

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_NO_MAGIC_SKILL));
  manager.send();
}
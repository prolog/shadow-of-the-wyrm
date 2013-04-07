#include "SpellcastingAction.hpp"
#include "Game.hpp"
#include "MagicalAbilityChecker.hpp"
#include "MessageManager.hpp"
#include "SpellcastingTextKeys.hpp"
#include "StringTable.hpp"

SpellcastingAction::SpellcastingAction()
{
}

ActionCostValue SpellcastingAction::cast_spell(CreaturePtr creature) const
{
  ActionCostValue action_cost_value = 0;

  if (creature)
  {
    MagicalAbilityChecker mac;

    if (mac.has_magical_knowledge(creature) == false)
    {
      if (creature->get_is_player())
      {
        add_no_magical_knowledge_message();
      }
    }
    else
    {
      Game& game = Game::instance();
      MapPtr current_map = game.get_current_map();

      if (current_map && current_map->get_map_type() == MAP_TYPE_WORLD)
      {
        add_invalid_spellcasting_location_message();
      }
      else
      {
        // JCD FIXME
      }
    }
  }

  return action_cost_value;
}

// Add a message that the player has no magical knowledge
void SpellcastingAction::add_no_magical_knowledge_message() const
{
  MessageManager& manager = MessageManager::instance();

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_NO_MAGICAL_KNOWLEDGE));
  manager.send();
}

// Add a message that spells can't be cast here (basically, world map)
void SpellcastingAction::add_invalid_spellcasting_location_message() const
{
  MessageManager& manager = MessageManager::instance();

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_UNAVAILABLE_ON_WORLD_MAP));
  manager.send();
}

ActionCostValue SpellcastingAction::get_action_cost_value() const
{
  return 1;
}
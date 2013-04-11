#include <boost/make_shared.hpp>
#include "Conversion.hpp"
#include "SpellcastingAction.hpp"
#include "Game.hpp"
#include "MagicalAbilityChecker.hpp"
#include "MagicCommandFactory.hpp"
#include "MagicCommandProcessor.hpp"
#include "MagicKeyboardCommandMap.hpp"
#include "MessageManager.hpp"
#include "SpellcastingTextKeys.hpp"
#include "SpellSelectionScreen.hpp"
#include "StringTable.hpp"

using namespace std;

SpellcastingAction::SpellcastingAction()
{
}

ActionCostValue SpellcastingAction::cast_spell(CreaturePtr creature) const
{
  ActionCostValue action_cost_value = 0;

  // variable used to control whether to keep looping for input on the 
  // spellcasting screen.
  bool cast_spells = true;

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
        if (creature->get_is_player())
        {
          CommandFactoryPtr command_factory    = boost::make_shared<MagicCommandFactory>();
          KeyboardCommandMapPtr kb_command_map = boost::make_shared<MagicKeyboardCommandMap>();

          Game& game = Game::instance();

          while (cast_spells)
          {
            SpellSelectionScreen sss(game.get_display(), creature);

            int input = sss.display().at(0);

            DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
      
            if (decision_strategy)
            {
              // Get the actual command, signalling to the decision function that
              // input has been provided (don't try to get the input twice).
              CommandPtr magic_command = decision_strategy->get_nonmap_decision(creature->get_id(), command_factory, kb_command_map, &input);

              action_cost_value = MagicCommandProcessor::process(creature, magic_command);
            }

            if (!decision_strategy || action_cost_value == -1)
            {
              cast_spells = false;
            }
          }
        }
        else
        {
          // JCD FIXME - Change this once creatures with magic are added to AI
          // considerations...
        }
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
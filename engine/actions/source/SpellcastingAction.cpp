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
#include "SpellShapeProcessorFactory.hpp"
#include "StringTable.hpp"
#include "TextMessages.hpp"

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

  // used to determine whether a spell was selected in the spellcasting screen.
  // if so, the spell will be cast at the end of the process.
  string spell_id;

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

            string display_s = sss.display();
            int input = display_s.at(0);
            char menu_selection = display_s.at(0);

            spell_id = sss.get_selected_spell(menu_selection);

            DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
      
            if (decision_strategy)
            {
              // Get the actual command, signalling to the decision function that
              // input has been provided (don't try to get the input twice).
              CommandPtr magic_command = decision_strategy->get_nonmap_decision(creature->get_id(), command_factory, kb_command_map, &input);

              action_cost_value = MagicCommandProcessor::process(creature, magic_command);

              if (action_cost_value > 0 && !spell_id.empty())
              {
                // A spell was selected, and the command processor will have
                // taken care of casting it.  Leave the menu and go back to
                // the map.
                cast_spells = false;
              }
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

  if ((action_cost_value > 0) && !spell_id.empty())
  {
    // First, re-display the contents of the map screen, since we would
    // have selected from a menu (in a different window):
    DisplayPtr display = Game::instance().get_display();
    display->redraw();

    action_cost_value = cast_spell(creature, spell_id);
  }

  return action_cost_value;
}

// Cast a particular spell by a particular creature.
ActionCostValue SpellcastingAction::cast_spell(CreaturePtr creature, const string& spell_id) const
{
  ActionCostValue action_cost_value = 0;
  MessageManager& manager = MessageManager::instance();

  if (creature)
  {
    Game& game = Game::instance();
    Spell spell = game.get_spells_ref().find(spell_id)->second;
    MagicalAbilityChecker mac;

    // Check to see if the creature has the AP for the spell.
    if (mac.has_sufficient_power(creature, spell))
    {
      action_cost_value = spell.get_speed();

      MapPtr current_map = game.get_current_map();
      Coordinate caster_coord = current_map->get_location(creature->get_id());

      // Reduce the creature's AP by the spell cost.
      Statistic new_ap = creature->get_arcana_points();
      new_ap.set_current(new_ap.get_current() - spell.get_ap_cost());
      creature->set_arcana_points(new_ap);

      // Add an appropriate casting message.
      string cast_message = TextMessages::get_spellcasting_message(spell, creature->get_description_sid(), creature->get_is_player());
      manager.add_new_message(cast_message);

      // Process the spell shape.
      SpellShapeProcessorPtr spell_processor = SpellShapeProcessorFactory::create_processor(spell.get_shape().get_spell_shape_type());
      
      if (spell_processor)
      {
        // JCD FIXME: Create animation and display it here.
        spell_processor->process(current_map, caster_coord, DIRECTION_NORTH /* JCD FIXME */, spell, &game.get_action_manager_ref());
      }

      // Send the cast message and any messages generating by hitting other
      // creatures, etc.
      manager.send();
    }
    else
    {
      add_insufficient_power_message();
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

// Add a message about not having enough AP.
void SpellcastingAction::add_insufficient_power_message() const
{
  MessageManager& manager = MessageManager::instance();

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_INSUFFICIENT_POWER));
  manager.send();
}

ActionCostValue SpellcastingAction::get_action_cost_value() const
{
  return 1;
}
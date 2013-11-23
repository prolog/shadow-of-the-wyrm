#include "ActionTextKeys.hpp"
#include "Commands.hpp"
#include "Conversion.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DirectionUtils.hpp"
#include "SpellcastingAction.hpp"
#include "Game.hpp"
#include "MagicalAbilityChecker.hpp"
#include "MagicCommandFactory.hpp"
#include "MagicCommandProcessor.hpp"
#include "MagicKeyboardCommandMap.hpp"
#include "MessageManagerFactory.hpp"
#include "SpellBonusUpdater.hpp"
#include "SpellcastingTextKeys.hpp"
#include "SpellSelectionScreen.hpp"
#include "SpellcastingProcessor.hpp"
#include "SpellShapeProcessorFactory.hpp"
#include "StringTable.hpp"

using namespace std;

SpellcastingAction::SpellcastingAction()
{
}

ActionCostValue SpellcastingAction::cast_spell(CreaturePtr creature) const
{
  ActionCostValue action_cost_value = 0;
  CurrentCreatureAbilities cca;

  // variable used to control whether to keep looping for input on the 
  // spellcasting screen.
  bool cast_spells = true;

  // used to determine whether a spell was selected in the spellcasting screen.
  // if so, the spell will be cast at the end of the process.
  string spell_id;

  if (cca.can_speak(creature, true))
  {
    MagicalAbilityChecker mac;

    if (mac.has_magical_knowledge(creature) == false)
    {
      if (creature->get_is_player())
      {
        add_no_magical_knowledge_message(creature);
      }
    }
    else
    {
      Game& game = Game::instance();
      MapPtr current_map = game.get_current_map();

      if (current_map && current_map->get_map_type() == MAP_TYPE_WORLD)
      {
        add_invalid_spellcasting_location_message(creature);
      }
      else
      {
        pair<string, ActionCostValue> spell_details = cast_spell_on_valid_map_type(creature);
        spell_id = spell_details.first;
        action_cost_value = spell_details.second;
      }
    }
  }

  if ((action_cost_value > 0) && !spell_id.empty())
  {
    // First, re-display the contents of the map screen, since we would
    // have selected from a menu (in a different window):
    Game& game = Game::instance();
    game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
    game.get_display()->redraw();

    action_cost_value = cast_spell(creature, spell_id);
  }

  return action_cost_value;
}

pair<string, ActionCostValue> SpellcastingAction::cast_spell_on_valid_map_type(CreaturePtr creature) const
{
  bool cast_spells = true;
  pair<string, ActionCostValue> selection_details("", 0);

  if (creature->get_is_player())
  {
    while (cast_spells)
    {
      pair<bool, pair<string, ActionCostValue>> cur_selection_details = process_spellcasting_selection(creature);
      cast_spells = cur_selection_details.first;
      selection_details = cur_selection_details.second;
    }
  }
  else
  {
    // JCD FIXME - Change this once creatures with magic are added to AI
    // considerations...
  }

  return selection_details;
}

// Cast a particular spell by a particular creature.
ActionCostValue SpellcastingAction::cast_spell(CreaturePtr creature, const string& spell_id) const
{
  ActionCostValue action_cost_value = 0;
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

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
      reduce_caster_ap_by_spell_cost(creature, spell);

      // A check to see if spellcasting succeeded.  If the spell is directional
      // and a proper direction isn't selected, this will cause the magic 
      // to fail.
      bool spellcasting_succeeded = true;
      Direction spell_direction = DIRECTION_NORTH;

      // Is a direction needed?
      if (spell.get_shape().get_direction_category() != DIRECTION_CATEGORY_NONE)
      {
        pair<bool, Direction> direction_pair = get_spell_direction_from_creature(creature, spell, spell_direction);
        spellcasting_succeeded = direction_pair.first; // Can the input be converted to a dir?
        spell_direction = direction_pair.second; // The actual direction, or the initial value if action conversion didn't work.
      }

      if (spellcasting_succeeded == false)
      {
        IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
        manager.add_new_message(ActionTextKeys::get_spellcasting_cancelled_message(creature->get_description_sid(), creature->get_is_player()));
      }
      else
      {
        // Add an appropriate casting message.
        string cast_message = ActionTextKeys::get_spellcasting_message(spell, creature->get_description_sid(), creature->get_is_player());
        manager.add_new_message(cast_message);

        // Reduce castings by one, removing the spell if there are none left.
        reduce_castings_or_remove_spell(creature, spell);

        // Mark the spell as the most recently cast.
        creature->get_spell_knowledge_ref().set_most_recently_cast_spell_id(spell.get_spell_id());

        // Process the spell shape.
        SpellShapeProcessorPtr spell_processor = SpellShapeProcessorFactory::create_processor(spell.get_shape().get_spell_shape_type());
      
        if (spell_processor)
        {
          SpellcastingProcessor sp;

          // Spells always use the "uncursed" effect status.
          sp.process(spell_processor, creature, current_map, caster_coord, spell_direction, spell, ITEM_STATUS_UNCURSED);
        }

        // Now that the spell has been cast, update the spell bonus information
        update_spell_bonus(creature, spell);
      }

      // Send the cast message and any messages generating by hitting other
      // creatures, etc.
      manager.send();
    }
    else
    {
      add_insufficient_power_message(creature);
    }
  }

  return action_cost_value;
}

void SpellcastingAction::update_spell_bonus(CreaturePtr caster, const Spell& spell) const
{
  string spell_id = spell.get_spell_id();

  SpellKnowledge& sk = caster->get_spell_knowledge_ref();
  IndividualSpellKnowledge isk = sk.get_spell_knowledge(spell_id);

  SpellBonusUpdater sbu;
  bool bonus_updated = sbu.add_successful_casting(isk);
  sk.set_spell_knowledge(spell_id, isk);
  
  if (bonus_updated && caster->get_is_player())
  {
    add_spell_bonus_increased_message(caster);
  }
}

// Add a message about the spell bonus increasing.
void SpellcastingAction::add_spell_bonus_increased_message(CreaturePtr creature) const
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_BONUS_INCREASED));
  manager.send();
}

// Add a message that the player has no magical knowledge
void SpellcastingAction::add_no_magical_knowledge_message(CreaturePtr creature) const
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_NO_MAGICAL_KNOWLEDGE));
  manager.send();
}

// Add a message that spells can't be cast here (basically, world map)
void SpellcastingAction::add_invalid_spellcasting_location_message(CreaturePtr creature) const
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_UNAVAILABLE_ON_WORLD_MAP));
  manager.send();
}

// Add a message about not having enough AP.
void SpellcastingAction::add_insufficient_power_message(CreaturePtr creature) const
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_INSUFFICIENT_POWER));
  manager.send();
}

ActionCostValue SpellcastingAction::get_action_cost_value() const
{
  return 1;
}

// Reduce the spellcaster's AP by the amount specified by the spell
void SpellcastingAction::reduce_caster_ap_by_spell_cost(CreaturePtr caster, const Spell& spell) const
{
  Statistic new_ap = caster->get_arcana_points();
  new_ap.set_current(new_ap.get_current() - spell.get_ap_cost());
  caster->set_arcana_points(new_ap);
}

// Reduce the number of castings by 1.  If there are 0 castings left, "remove" the
// spell by setting its castings to 0.  Keeping the spell around ensures that any
// bonuses, etc., remain after "re-learning" the spell.
void SpellcastingAction::reduce_castings_or_remove_spell(CreaturePtr caster, const Spell& spell) const
{
  string spell_id = spell.get_spell_id();

  SpellKnowledge& sk = caster->get_spell_knowledge_ref();
  IndividualSpellKnowledge isk = sk.get_spell_knowledge(spell_id);
  int new_castings = isk.get_castings() - 1;
  isk.set_castings(new_castings);
  sk.set_spell_knowledge(spell_id, isk);
}

// Get a direction for the spell from the creature.
// Also get whether the direction was "converted" properly from the base command
// (ie, was it a direction command?)
pair<bool, Direction> SpellcastingAction::get_spell_direction_from_creature(CreaturePtr creature, const Spell& spell, const Direction spell_direction) const
{
  bool direction_conversion_ok = true;
  Direction direction = spell_direction;

  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  // Make the creature select a direction.
  CommandFactoryPtr command_factory = std::make_shared<CommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_shared<KeyboardCommandMap>();

  // If the creature is the player, inform the player that a direction is needed.
  if (creature->get_is_player())
  {
    string direction_prompt_sid = ActionTextKeys::ACTION_GET_DIRECTION;
    if (spell.get_shape().get_direction_category() == DIRECTION_CATEGORY_CARDINAL)
    {
      direction_prompt_sid = ActionTextKeys::ACTION_GET_CARDINAL_DIRECTION;
    }

    manager.add_new_message(StringTable::get(direction_prompt_sid));
    manager.send();
  }

  // Try to get a direction.  This might fail.
  CommandPtr base_command = creature->get_decision_strategy()->get_nonmap_decision(false, creature->get_id(), command_factory, kb_command_map, 0);

  if (base_command)
  {
    // Check to see if it's an actual directional command
    std::shared_ptr<DirectionalCommand> dcommand;
    dcommand = std::dynamic_pointer_cast<DirectionalCommand>(base_command);

    if (dcommand)
    {
      // Clear the message manager.
      manager.clear_if_necessary();
      
      direction = dcommand->get_direction();
      DirectionCategory dc = spell.get_shape().get_direction_category();

      // Any directional spell must be at least cardinal.
      if (!DirectionUtils::is_cardinal(direction))
      {
        bool is_ordinal = DirectionUtils::is_ordinal(direction);

        // However, some spells (beams, etc) can also be
        // ordinal.
        if (dc == DIRECTION_CATEGORY_CARDINALORDINAL && !is_ordinal)
        {
          direction_conversion_ok = false;
        }

        if (is_ordinal && dc != DIRECTION_CATEGORY_CARDINALORDINAL)
        {
          direction_conversion_ok = false;
        }
      }
    }
    else
    {
      direction_conversion_ok = false;
    }
  }
  else
  {
    direction_conversion_ok = false;
  }

  pair<bool, Direction> direction_status(direction_conversion_ok, direction);
  return direction_status;
}

// Process spellcasting selections on the Cast Spells screen. Return false
// if processing should repeat (that is, return false if a spell has been
// selected - return true if the input does not allow exiting the Cast
// Spell screen).
pair<bool, pair<string, ActionCostValue>> SpellcastingAction::process_spellcasting_selection(CreaturePtr creature) const
{
  ActionCostValue action_cost_value = 0;
  bool cast_spells = true;

  Game& game = Game::instance();
  SpellSelectionScreen sss(game.get_display(), creature);

  string display_s = sss.display();
  int input = display_s.at(0);
  char menu_selection = display_s.at(0);

  string spell_id = sss.get_selected_spell(menu_selection);

  DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
  CommandFactoryPtr command_factory    = std::make_shared<MagicCommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_shared<MagicKeyboardCommandMap>();

  if (decision_strategy)
  {
    // Get the actual command, signalling to the decision function that
    // input has been provided (don't try to get the input twice).
    CommandPtr magic_command = decision_strategy->get_nonmap_decision(false, creature->get_id(), command_factory, kb_command_map, &input);

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

  pair<bool, pair<string, ActionCostValue>> selection_and_cost(cast_spells, make_pair(spell_id, action_cost_value));
  return selection_and_cost;
}
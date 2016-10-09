#include "ActionManager.hpp"
#include "ActionTextKeys.hpp"
#include "Commands.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DirectionUtils.hpp"
#include "EffectFactory.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SkillManager.hpp"
#include "SpellConstants.hpp"
#include "SpellcastingProcessor.hpp"
#include "SpellShapeFactory.hpp"
#include "SpellShapeProcessorFactory.hpp"
#include "EvokeAction.hpp"
#include "StatisticsMarker.hpp"
#include "WandCalculator.hpp"

using namespace std;
using std::dynamic_pointer_cast;

// Select a wand to evoke
ActionCostValue EvokeAction::evoke(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue action_cost_value = 0;
  CurrentCreatureAbilities cca;

  if (cca.can_speak(creature, true))
  {
    list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_type_filter(ItemType::ITEM_TYPE_WAND);
    ItemPtr selected_item = am->inventory(creature, creature->get_inventory(), display_filter_list, {}, false);
    
    if (selected_item)
    {
      WandPtr wand = dynamic_pointer_cast<Wand>(selected_item);
      
      if (wand)
      {
        // Redraw the screen, since we will have moved from the evoke screen
        // back to the main map.
        Game& game = Game::instance();
        game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
        game.get_display()->redraw();

        WandPtr new_wand;
        bool need_to_remove_before_adding_or_merging = false;

        if (wand->get_quantity() > 1)
        {
          wand->set_quantity(wand->get_quantity() - 1);
          ItemPtr new_wand_as_item = ItemPtr(wand->clone());
          new_wand = dynamic_pointer_cast<Wand>(new_wand_as_item);
        }
        else
        {
          need_to_remove_before_adding_or_merging = true;
          new_wand = wand;
        }

        // Try to evoke the item
        action_cost_value = evoke_wand(creature, am, new_wand);

        // Remove the item before re-adding it: used when there is only
        // a single wand.
        if (need_to_remove_before_adding_or_merging)
        {
          creature->get_inventory()->remove(wand->get_id());
        }

        // Insert the item back into the inventory.
        // This will take care of de-stacking/re-stacking and ensuring that
        // like-items are grouped together.
        creature->get_inventory()->merge_or_add(new_wand, InventoryAdditionType::INVENTORY_ADDITION_BACK);
      }
    }
  }
  
  return action_cost_value;
}

// A wand was selected.  Evoke it: apply any damage, and then do the magical effect.
ActionCostValue EvokeAction::evoke_wand(CreaturePtr creature, ActionManager * const am, WandPtr wand)
{
  ActionCostValue action_cost_value = 0;

  if (creature && wand)
  {
    EffectType et = wand->get_effect_type();
    EffectPtr wand_effect = EffectFactory::create_effect(et);
    
    if (wand_effect)
    {
      ItemIdentifier item_id;
      string wand_base_id = wand->get_base_id();
      bool wand_originally_identified = item_id.get_item_identified(wand_base_id);

      // Get the wand's direction.
      bool evoke_successful = true;
      pair<bool, Direction> evoke_result = { true, Direction::DIRECTION_NULL };
      SpellShapeType shape_type = wand->get_spell_shape_type();

      if (shape_type != SpellShapeType::SPELL_SHAPE_BALL)
      {
        evoke_result = get_evocation_direction(creature, shape_type);
        evoke_successful = evoke_result.first;
      }

      if (evoke_successful)
      {
        Game& game = Game::instance();
        MapPtr map = game.get_current_map();
        Coordinate caster_coord = map->get_location(creature->get_id());

        // Create a temporary spell based on the wand's characteristics.
        Spell wand_spell = create_wand_spell(creature, wand, evoke_result.second);

        // Add a message about evoking.
        add_evocation_message(creature, wand, item_id);
      
        // Train Wandcraft
        SkillManager sm;
        sm.mark_skill(creature, SkillType::SKILL_GENERAL_WANDCRAFT, true);

        // Reduce the charges on the wand.
        Statistic original_charges = wand->get_charges();
        reduce_wand_charges_if_necessary(creature, wand);

        // Process the damage and spell on the wand.  If there are no charges,
        // the effect returned will be null, and has_damage will return false.
        bool wand_identified = process_wand_damage_and_effect(creature, map, caster_coord, evoke_result.second, wand_spell, wand->get_status(), original_charges);

        // If the wand was identified during use, name it.
        name_wand_if_identified(creature, wand, wand_identified, wand_originally_identified, item_id);

        // If this is a useful wand (effect type isn't null), train willpower.
        if (et != EffectType::EFFECT_TYPE_NULL)
        {
          StatisticsMarker sm;
          sm.mark_willpower(creature);
        }

        action_cost_value = get_action_cost_value(creature);
      }
      else
      {
        // Add a message about the unsuccessful attempt.
        if (creature && creature->get_is_player())
        {
          IMessageManager& manager = MM::instance();
          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_EVOKE_FAILED));
          manager.send();
        }
      }
    }
  }

  return action_cost_value;
}

void EvokeAction::add_evocation_message(CreaturePtr creature, WandPtr wand, const ItemIdentifier& item_id)
{
  EffectPtr effect = EffectFactory::create_effect(wand->get_effect_type());
  
  // Get "You/monster evoke a wand" message
  string evoke_message = ActionTextKeys::get_evoke_message(creature->get_description_sid(), item_id.get_appropriate_usage_description(wand), creature->get_is_player());
  
  // Display an appropriate message
  IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
  
  manager.add_new_message(evoke_message);
  manager.send();
}

// Get the basic cost of evoking a wand.
ActionCostValue EvokeAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}

pair<bool, Direction> EvokeAction::get_evocation_direction(CreaturePtr creature, const SpellShapeType shape_type)
{
  pair<bool, Direction> evoke_direction_result(false, Direction::DIRECTION_UP);

  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  // Make the creature select a direction.
  CommandFactoryPtr command_factory = std::make_shared<CommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_shared<KeyboardCommandMap>();
  SpellShape spell_shape = SpellShapeFactory::create_spell_shape(shape_type, SpellConstants::DEFAULT_BEAM_RADIUS);

  // If the creature is the player, inform the player that a direction is needed.
  if (creature->get_is_player())
  {
    string direction_prompt_sid = ActionTextKeys::ACTION_GET_DIRECTION;

    if (spell_shape.get_direction_category() == DirectionCategory::DIRECTION_CATEGORY_CARDINAL)
    {
      direction_prompt_sid = ActionTextKeys::ACTION_GET_CARDINAL_DIRECTION;
    }

    manager.add_new_message(StringTable::get(direction_prompt_sid));
    manager.send();
  }

  CommandPtr base_command = creature->get_decision_strategy()->get_nonmap_decision(false, creature->get_id(), command_factory, kb_command_map, 0);

  if (base_command)
  {
    // Check to see if it's an actual directional command
    std::shared_ptr<DirectionalCommand> dcommand;
    dcommand = std::dynamic_pointer_cast<DirectionalCommand>(base_command);

    if (dcommand && (DirectionUtils::direction_matches_category(dcommand->get_direction(), spell_shape.get_direction_category())))
    {
      evoke_direction_result.first = true;
      evoke_direction_result.second = dcommand->get_direction();
    }
  }

  return evoke_direction_result;
}

// Create a temporary spell for use by the spell processor, based on the
// wand's characteristics.
Spell EvokeAction::create_wand_spell(CreaturePtr creature, WandPtr wand, const Direction dir) const
{
  Spell wand_spell;

  wand_spell.set_has_damage(wand->get_has_damage());

  Damage dmg = wand->get_damage();

  wand_spell.set_effect(wand->get_effect_type());

  WandCalculator wc;
  int damage_bonus = wc.calc_damage_bonus(creature);
  dmg.set_modifier(dmg.get_modifier() + damage_bonus);
  wand_spell.set_damage(wand->get_damage());

  if (dir == Direction::DIRECTION_NULL)
  {
    wand_spell.set_range(1);
  }
  else
  {
    wand_spell.set_range(wand->get_range());
  }

  wand_spell.set_allows_bonus(false);
  wand_spell.set_shape(SpellShapeFactory::create_spell_shape(wand->get_spell_shape_type(), SpellConstants::DEFAULT_BEAM_RADIUS));
  wand_spell.set_colour(wand->get_spell_colour());

  return wand_spell;
}

// If the wand has any charges left, reduce the total number of charges by 1.
void EvokeAction::reduce_wand_charges_if_necessary(CreaturePtr creature, WandPtr wand) const
{
  Statistic charges = wand->get_charges();

  if (charges.get_current() > 0)
  {
    WandCalculator wc;
    if (RNG::percent_chance(wc.calc_pct_chance_free_charge(creature)) == false)
    {
      charges.set_current(charges.get_current() - 1);
      wand->set_charges(charges);
    }
  }
}

// Process the actual damage and effect on the wand.  Return true if the wand
// was identified while doing this, false otherwise.
bool EvokeAction::process_wand_damage_and_effect(CreaturePtr creature, MapPtr map, const Coordinate& caster_coord, const Direction direction, const Spell& wand_spell, const ItemStatus wand_status, const Statistic& original_charges)
{
  bool wand_identified = false;

  if (original_charges.get_current() > 0)
  {
    // Process the effect.  This will do any necessary updates/damage to the creature, and will also
    // add a status message based on whether the item was identified.
    SpellShapeProcessorPtr spell_processor = SpellShapeProcessorFactory::create_processor(wand_spell.get_shape().get_spell_shape_type());

    if (spell_processor)
    {
      // Use the generic spell processor, which is also used for "regular"
      // spellcasting.
      SpellcastingProcessor sp;
      wand_identified = sp.process(spell_processor, creature, map, caster_coord, direction, wand_spell, wand_status);
    }
  }
  else
  {
    if (creature && creature->get_is_player())
    {
      IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, true);
      manager.add_new_message(StringTable::get(EffectTextKeys::EFFECT_NULL));
      manager.send();
    }
  }

  return wand_identified;
}

void EvokeAction::name_wand_if_identified(CreaturePtr creature, WandPtr wand, const bool wand_identified, const bool wand_originally_identified, const ItemIdentifier& item_id) const
{
  // Was the item identified?
  if (wand && wand_identified)
  {        
    // If the item was not identified prior to quaffing, identify it now.
    if (!wand_originally_identified)
    {
      item_id.set_item_identified(creature, wand, wand->get_base_id(), true);
    }
  }
}

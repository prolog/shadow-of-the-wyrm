#include "ActionManager.hpp"
#include "ActionTextKeys.hpp"
#include "ConsumableAction.hpp"
#include "CreatureUtils.hpp"
#include "EffectFactory.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "QuaffAction.hpp"
#include "SpellFactory.hpp"
#include "SpellShapeProcessorFactory.hpp"
#include "SpellcastingProcessor.hpp"
#include "StatisticsMarker.hpp"
#include "TextMessages.hpp"

using namespace std;
using std::dynamic_pointer_cast;

bool QuaffAction::operator==(const QuaffAction& qm) const
{
  return true;
}

// Select a potion to quaff
ActionCostValue QuaffAction::quaff(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  
  if (creature)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    
    list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_type_filter(ItemType::ITEM_TYPE_POTION);
    TilePtr tile = MapUtils::get_tile_for_creature(current_map, creature);
    IInventoryPtr inventory = creature->get_inventory();

    action_cost_value = quaff_potion_off_ground(creature, display_filter_list);

    if (action_cost_value == 0)
    {
      ItemPtr selected_item = am->inventory(creature, creature->get_inventory(), display_filter_list, {}, false, false);

      if (selected_item)
      {
        PotionPtr potion = dynamic_pointer_cast<Potion>(selected_item);

        if (potion)
        {
          ItemIdentifier item_id;
          string base_id = potion->get_base_id();

          // Get "You/monster quaffs a foo-ey potion" message
          string quaff_message = ActionTextKeys::get_quaff_message(creature->get_description_sid(), item_id.get_appropriate_usage_description(potion), creature->get_is_player());

          quaff_potion(creature, potion, creature, inventory, quaff_message);
          action_cost_value = get_action_cost_value(creature);
        }
      }
    }
  }
  
  return action_cost_value;
}

ActionCostValue QuaffAction::quaff_potion_off_ground(CreaturePtr creature, const list<IItemFilterPtr>& display_filters)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  MapPtr current_map = Game::instance().get_current_map();
  TilePtr tile = MapUtils::get_tile_for_creature(current_map, creature);

  if (tile)
  {
    IInventoryPtr items = tile->get_items();
    list<ItemPtr> potable_ground = ItemManager::get_filtered_items(items, display_filters);

    // For each item on the ground, check with the creature to see if they 
    // want to eat it.
    for (ItemPtr potion : potable_ground)
    {
      ItemIdentifier iid;

      string consumable_desc = iid.get_appropriate_usage_description(potion);
      IMessageManager& manager = MM::instance();
      manager.clear_if_necessary();
      manager.add_new_confirmation_message(TextMessages::get_confirmation_message(ActionTextKeys::get_quaff_confirmation_message(consumable_desc)));
      bool confirm = creature->get_decision_strategy()->get_confirmation();

      if (confirm)
      {
        PotionPtr ppotion = std::dynamic_pointer_cast<Potion>(potion);

        if (ppotion != nullptr)
        {
          string quaff_message = ActionTextKeys::get_quaff_message(creature->get_description_sid(), iid.get_appropriate_usage_description(potion), creature->get_is_player());
          quaff_potion(creature, ppotion, creature, items, quaff_message);
          action_cost_value = get_action_cost_value(creature);
          break;  
        }
      }
    }
  }

  return action_cost_value;
}

void QuaffAction::explode_potion(CreaturePtr original_attacker, CreaturePtr creature_by_exploding_potion, PotionPtr potion)
{
  if (creature_by_exploding_potion && potion)
  {
    IInventoryPtr inv;

    if (original_attacker != nullptr)
    {
      inv = original_attacker->get_inventory();
    }

    string message = StringTable::get(ActionTextKeys::ACTION_POTION_EXPLODES);
    quaff_potion(creature_by_exploding_potion, potion, original_attacker, inv, message);
  }
}

// A valid potion's been selected.  Quaff it: get the potion's nutrition, and then do the magical effect.
void QuaffAction::quaff_potion(CreaturePtr creature, PotionPtr potion, CreaturePtr caster, IInventoryPtr inventory, const string& message)
{
  if (creature != nullptr && potion != nullptr && inventory != nullptr)
  {
    string caster_id = caster != nullptr ? caster->get_id() : "";

    EffectType et = potion->get_effect_type();
    EffectPtr potion_effect = EffectFactory::create_effect(et, {}, {}, "", caster_id);

    if (potion_effect)
    {
      Game& game = Game::instance();
      MapPtr map = game.get_current_map();
      Coordinate caster_coord = map->get_location(creature->get_id());

      ItemIdentifier item_id;
      string potion_base_id = potion->get_base_id();
      bool potion_originally_identified = item_id.get_item_identified(potion_base_id);

      // Add a message about quaffing.
      add_quaff_message(creature, message);
      
      // Reduce the quantity, removing it from the inventory if necessary
      potion->set_quantity(potion->get_quantity() - 1);
      if (potion->get_quantity() == 0) inventory->remove(potion->get_id());
      
      // Process the effect using a temporary spell.  This will do any necessary 
      // updates to the creature, and will also add a status message based on
      // whether the item was identified.
      Spell potion_spell = create_potion_spell(potion); 

      SpellShapeProcessorPtr spell_processor = SpellShapeProcessorFactory::create_processor(potion_spell.get_shape().get_spell_shape_type());
      bool effect_identified = false;

      if (spell_processor != nullptr)
      {
        // Use the generic spell processor, which is also used for "regular"
        // spellcasting.
        SpellcastingProcessor sp;
        effect_identified = sp.process(spell_processor.get(), caster, map, caster_coord, Direction::DIRECTION_NULL, potion_spell, 0, potion->get_status());
      }

      // Was the item identified?
      if (effect_identified)
      {        
        // If the item was not identified prior to quaffing, identify it now.
        if (!potion_originally_identified)
        {
          item_id.set_item_identified(creature, potion, potion_base_id, true);
        }
      }

      ConsumableAction ca;
      ca.consume(creature, potion, false /* don't process effect */);

      // If there's actually an effect (ie, this isn't booze, fruit juice, etc)
      // then mark willpower, as it takes nerve to pound magical potions.
      if (et != EffectType::EFFECT_TYPE_NULL)
      {
        StatisticsMarker sm;
        sm.mark_willpower(creature);
      }
    }
  }
}

Spell QuaffAction::create_potion_spell(PotionPtr potion)
{
  Spell potion_spell = SpellFactory::create_self_targetted_item_spell();

  // If the potion can damage the drinker (potion of fire, etc), ensure that
  // the damage is added to the potion spell.
  if (potion->get_has_damage())
  {
    potion_spell.set_has_damage(true);
    potion_spell.set_damage(potion->get_damage());
  }

  potion_spell.set_effect(potion->get_effect_type());
  potion_spell.set_modifier(potion->get_modifier());

  return potion_spell;
}

void QuaffAction::add_quaff_message(CreaturePtr creature, const string& quaff_message)
{
  // Display an appropriate message
  IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
  
  manager.add_new_message(quaff_message);
  manager.send();
}

ActionCostValue QuaffAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}

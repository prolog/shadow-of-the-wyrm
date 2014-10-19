#include "OfferAction.hpp"
#include "ActionManager.hpp"
#include "ActionTextKeys.hpp"
#include "AlignmentCalculator.hpp"
#include "ClassManager.hpp"
#include "CreatureUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DeityDecisionStrategyFactory.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemPietyCalculator.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "ReligionManager.hpp"
#include "RNG.hpp"
#include "SacrificeTextKeys.hpp"

using namespace std;

OfferAction::OfferAction()
{
}

// Sacrifice an item to one's deity.
ActionCostValue OfferAction::offer(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue acv = 0;

  if (creature)
  {
    // Is the creature on an altar?
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    TilePtr tile = MapUtils::get_tile_for_creature(current_map, creature);
    FeaturePtr feature = tile->get_feature();

    // On an altar - pick an item to sacrifice
    if (tile && feature && feature->can_offer())
    {
      acv = sacrifice_item(creature, feature, am);
    }
    else
    {
      add_no_altar_message(creature);
    }
  }

  return acv;
}

// Prompt the creature to select an item for sacrifice.
ActionCostValue OfferAction::sacrifice_item(CreaturePtr creature, FeaturePtr feature, ActionManager * const am)
{
  ActionCostValue acv = 0;

  if (creature)
  {
    IMessageManager& manager = MessageManagerFactory::instance();

    if (creature->get_inventory()->empty() && creature->get_is_player())
    {
      manager.add_new_message(StringTable::get(SacrificeTextKeys::SACRIFICE_NO_ITEMS));
      manager.send();
    }
    else
    {
      acv = get_action_cost_value(creature);

      list<IItemFilterPtr> no_filter = ItemFilterFactory::create_empty_filter();
      ItemPtr item_to_sac = am->inventory(creature, creature->get_inventory(), no_filter, false);

      if (item_to_sac == nullptr)
      {
        manager.add_new_message(StringTable::get(SacrificeTextKeys::SACRIFICE_NO_ITEM_SELECTED));
        manager.send();
      }
      else
      {
        // Item disappears.
        CurrentCreatureAbilities cca;
        string message = SacrificeTextKeys::get_sacrifice_message(feature->get_alignment_range(), 
                                                                  item_to_sac, 
                                                                  !cca.can_see(creature));
        manager.add_new_message(message);
        manager.send();

        // Deity accepts the sacrifice, altar is converted, etc.
        bool item_accepted = handle_sacrifice(creature, feature, item_to_sac);

        if (!item_accepted)
        {
          // Nothing happened.  Add a message.
          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_NOTHING_HAPPENS));
          manager.send();
        }

        // Now that it's been dealt with, remove it from the inventory.
        creature->get_inventory()->remove(item_to_sac->get_id());
      }
    }
  }

  return acv;
}

// - If the altar is co-aligned (same status as creature), sacrifice to that
//   creature's deity.
//
// - If the altar is cross-aligned (different status as creature), there is
//   a chance, based on the value of the item, to either:
//
//   - Move the creature's alignment towards the altar.
//
//   - Convert the altar to the creature's alignment.
bool OfferAction::handle_sacrifice(CreaturePtr creature, FeaturePtr feature, ItemPtr item)
{
  if (creature && feature && item)
  {
    AlignmentRange creature_alignment = creature->get_alignment().get_alignment_range();
    AlignmentRange altar_alignment = feature->get_alignment_range();

    if (creature_alignment == altar_alignment)
    {
      return sacrifice_on_own_altar(creature, feature, item);
    }
    else
    {
      return sacrifice_on_other_altar(creature, feature, item);
    }
  }

  return false;
}

// Sacrifice on an altar of the creature's own alignment.  This is the simplest
// case: the sacrifice is offered to the creature's own deity.
bool OfferAction::sacrifice_on_own_altar(CreaturePtr creature, FeaturePtr feature, ItemPtr item)
{
  bool result = false;

  if (creature && item)
  {
    Game& game = Game::instance();
    TilePtr creature_tile = MapUtils::get_tile_for_creature(game.get_current_map(), creature);

    // Does anything happen as a result?
    ReligionManager rm;
    DeityPtr deity = rm.get_active_deity(creature);

    IDeityDecisionStrategyPtr deity_decision_strategy = DeityDecisionStrategyFactory::create_deity_decision_strategy(deity->get_id());
    DeityDecisionStrategyHandlerPtr deity_decision_handler = deity_decision_strategy->get_decision_for_sacrifice(creature, item);

    DeityDecisionImplications decision_implications = deity_decision_handler->handle_decision(creature, creature_tile);

    // Adjust piety and alignment.
    int piety = adjust_creature_piety(creature, decision_implications);

    AlignmentCalculator ac;
    int new_alignment = ac.calculate_alignment_for_sacrifice_on_coaligned_altar(creature->get_alignment().get_alignment(), feature->get_alignment_range());
    CreatureUtils::handle_alignment_change(creature, new_alignment);
    
    if (piety > 0)
    {
      result = true;
    }

    add_piety_message_if_player(creature);
  }

  return result;
}

// Sacrifice on a cross-aligned altar.  This has a chance to:
// - convert the altar
// - draw the creature's alignment closer to the alignment of the altar,
//   converting the creature to a random deity of that range if the creature's
//   alignment crosses over.
bool OfferAction::sacrifice_on_other_altar(CreaturePtr creature, FeaturePtr feature, ItemPtr item)
{
  bool result = false;

  if (creature && item)
  {
    AlignmentCalculator ac;
    int new_alignment = ac.calculate_alignment_for_sacrifice_on_crossaligned_altar(creature->get_alignment().get_alignment(), creature->get_alignment().get_alignment_range(), feature->get_alignment_range());
    int pct_chance_altar_conversion = ac.calculate_pct_chance_for_altar_conversion(item, creature->get_alignment().get_alignment_range(), feature->get_alignment_range());

    if (RNG::percent_chance(pct_chance_altar_conversion))
    {
      AlignmentRange creature_range = creature->get_alignment().get_alignment_range();
      new_alignment = ac.calculate_alignment_for_sacrifice_on_coaligned_altar(creature->get_alignment().get_alignment(), feature->get_alignment_range());
      
      // Create new altar, add it to tile.
      // ...

      // Add a message about the altar's conversion.
      // ...
    }

    CreatureUtils::handle_alignment_change(creature, new_alignment);

    result = true;
  }

  return result;
}

// Alter the creature's piety as a result of the sacrifice.
int OfferAction::adjust_creature_piety(CreaturePtr creature, const DeityDecisionImplications& decision_implications)
{
  int piety_gain = decision_implications.get_piety_gain();

  // Get the deity and the creature's status with that deity.
  ReligionManager rm;
  ClassManager cm;

  Religion& religion = creature->get_religion_ref();
  string deity_id = religion.get_active_deity_id();
  DeityPtr creature_deity = rm.get_deity(deity_id);
  DeityStatus status = religion.get_deity_status(deity_id);

  ClassPtr cur_class = cm.get_class(creature->get_class_id());

  status.increment_piety(piety_gain);
  religion.set_deity_status(deity_id, status);

  return piety_gain;
}

void OfferAction::add_no_altar_message(CreaturePtr creature)
{
  // No altar or other sacrifice-enabled feature present.
  if (creature->get_is_player())
  {
    string no_altar_msg = StringTable::get(SacrificeTextKeys::SACRIFICE_NO_ALTAR);
    IMessageManager& manager = MessageManagerFactory::instance();

    manager.add_new_message(no_altar_msg);
    manager.send();
  }
}

void OfferAction::add_piety_message_if_player(CreaturePtr creature)
{
  if (creature->get_is_player())
  {
    ReligionManager rm;
    int new_creature_piety = rm.get_piety_for_active_deity(creature);

    IMessageManager& manager = MessageManagerFactory::instance();
    string sac_piety_message = SacrificeTextKeys::get_piety_message(new_creature_piety);

    manager.add_new_message(sac_piety_message);
    manager.send();
  }
}

ActionCostValue OfferAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}


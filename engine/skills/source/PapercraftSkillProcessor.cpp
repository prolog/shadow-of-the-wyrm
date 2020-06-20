#include "PapercraftSkillProcessor.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemManager.hpp"
#include "MessageManagerFactory.hpp"
#include "PapercraftCalculator.hpp"
#include "RNG.hpp"
#include "SkillManager.hpp"

using namespace std;

// If the creature is holding a mold and deckle, and has enough paper pulp, 
// potentially create a number of blank scrolls (dependent on the amount
// of pulp being used).
ActionCostValue PapercraftSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION_MENU;

  if (creature && map)
  {
    IMessageManager& manager = MessageManagerFactory::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

    if (check_for_equipment(creature, manager))
    {
      ItemPtr pulp = select_pulp_pile(creature);
      const ItemMap items = Game::instance().get_items_ref();
      auto i_it = items.find(ItemIdKeys::ITEM_ID_BLANK_SCROLL);
      ItemPtr blank_scroll;

      if (i_it != items.end())
      {
        blank_scroll = i_it->second;
      }

      if (check_pulp_weight(blank_scroll, pulp, manager))
      {
        PapercraftCalculator pc;
        string outcome_message = ActionTextKeys::ACTION_PAPERCRAFT_FAILURE;
        bool created_scroll = false;

        if (RNG::percent_chance(pc.calculate_pct_chance_success(creature)))
        {
          created_scroll = true;

          outcome_message = ActionTextKeys::ACTION_PAPERCRAFT_SUCCESS;
          Weight bs_w = blank_scroll->get_weight();

          add_blank_scrolls_to_creature_tile(creature, map, bs_w, pulp->get_weight());
        }

        SkillManager sm;
        sm.mark_skill(creature, SkillType::SKILL_GENERAL_PAPERCRAFT, created_scroll);

        creature->get_inventory()->remove(pulp->get_id());
        

        manager.add_new_message(StringTable::get(outcome_message));
        manager.send();

        acv = get_default_skill_action_cost_value(creature);
      }
    }
  }

  return acv;
}

SkillProcessorPtr PapercraftSkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<PapercraftSkillProcessor>();
  return proc;
}

// Check to see if the creature has the right equipment for papermaking.
bool PapercraftSkillProcessor::check_for_equipment(CreaturePtr creature, IMessageManager& manager)
{
  bool has_eq = false;

  if (creature != nullptr)
  {
    ItemPtr wielded = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
    ItemPtr off_hand = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND);
    string check_id = ItemIdKeys::ITEM_ID_MOLD_AND_DECKLE;

    if ((wielded && wielded->get_base_id() == check_id) ||
        (off_hand && off_hand->get_base_id() == check_id))
    {
      has_eq = true;
    }
    else
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_PAPERCRAFT_NO_EQUIPMENT));
      manager.send();

      return false;
    }

    check_id = ItemIdKeys::ITEM_ID_PAPER_PULP;

    if (creature->get_inventory()->get_from_base_id(check_id) != nullptr)
    {
      has_eq = true;
    }
    else
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_PAPERCRAFT_NO_PULP));
      manager.send();

      return false;
    }
  }

  return has_eq;
}

// Check the weight of the selected paper pulp against that of the blank
// scroll template.  The pulp must weigh more to create scroll(s).
bool PapercraftSkillProcessor::check_pulp_weight(ItemPtr blank_scroll, ItemPtr pulp, IMessageManager& manager)
{
  bool weight_ok = false;

  if (blank_scroll != nullptr && pulp != nullptr)
  {
    Weight bs_weight = blank_scroll->get_weight();

    weight_ok = (pulp->get_weight() >= bs_weight);

    if (!weight_ok)
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_PAPERCRAFT_PULP_TOO_LIGHT));
    }
  }

  return weight_ok;
}

ItemPtr PapercraftSkillProcessor::select_pulp_pile(CreaturePtr creature)
{
  ItemPtr selected;

  if (creature != nullptr)
  {
    list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_base_id_filter(ItemIdKeys::ITEM_ID_PAPER_PULP);
    selected = Game::instance().get_action_manager_ref().inventory(creature, creature->get_inventory(), display_filter_list, {}, false);
  }

  return selected;
}

void PapercraftSkillProcessor::add_blank_scrolls_to_creature_tile(CreaturePtr creature, MapPtr map, const Weight& bs_w, const Weight& pulp_w)
{
  if (creature != nullptr && map != nullptr)
  {
    uint num_scrolls = static_cast<uint>(std::max(1u, pulp_w.get_weight() / bs_w.get_weight()));
    ItemPtr new_scrolls = ItemManager::create_item(ItemIdKeys::ITEM_ID_BLANK_SCROLL, num_scrolls);

    TilePtr tile = map->get_tile_at_location(creature->get_id());

    if (tile != nullptr)
    {
      tile->get_items()->merge_or_add(new_scrolls, InventoryAdditionType::INVENTORY_ADDITION_BACK);
    }
  }
}

ActionCostValue PapercraftSkillProcessor::get_default_skill_action_cost_value(CreaturePtr creature) const
{
  return -1;
}

#include "ActionTextKeys.hpp"
#include "FletcherySkillProcessor.hpp"
#include "CreateItemCalculator.hpp"
#include "CreateItemScreen.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"

using namespace std;

ActionCostValue FletcherySkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = -1;

  if (creature != nullptr && map != nullptr)
  {
    if (check_for_branch(creature))
    {
      CurrentCreatureAbilities cca;

      if (cca.can_see(creature, true))
      {
        Game& game = Game::instance();
        DisplayPtr cur_disp = game.get_display();

        CreateItemScreen cis(cur_disp, SkillType::SKILL_GENERAL_FLETCHERY);
        string sel = cis.display();
        char sel_c = sel.at(0) - 'a';
        OptionPtr option = cis.get_option(sel_c);

        if (option != nullptr)
        {
          string item_base_id = option->get_external_id();
          create_projectiles(item_base_id, creature, map);

          acv = get_default_skill_action_cost_value(creature);
        }
      }
    }
  }

  return acv;
}

bool FletcherySkillProcessor::check_for_branch(CreaturePtr creature)
{
  bool has_branch = false;

  if (creature != nullptr)
  {
    ItemPtr branch = creature->get_inventory()->get_from_base_id(ItemIdKeys::ITEM_ID_BRANCH);

    if (branch != nullptr)
    {
      has_branch = true;
    }
  }

  if (has_branch == false)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FLETCHERY_INSUFFICIENT_COMPONENTS));
    manager.send();
  }

  return has_branch;
}

void FletcherySkillProcessor::create_projectiles(const string& item_base_id, CreaturePtr creature, MapPtr map)
{
  // Remove the branch, and create a number of projectiles proportional to
  // the weight of the branch divided by the weight of the projectiles.
  ItemPtr item = ItemManager::create_item(item_base_id);
  TilePtr tile = MapUtils::get_tile_for_creature(map, creature);

  if (item != nullptr && tile != nullptr)
  {
    // Item's created.  Improve it appropriately.  Smith it
    // based on the improvement points;
    CreateItemCalculator cic;
    int potential_points = cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_FLETCHERY);
    int improvement_points = 0;

    if (potential_points > 0)
    {
      improvement_points = RNG::range(1, potential_points);
      item->set_remaining_smithings(improvement_points);
    }
    
    for (int i = 0; i < improvement_points; i++)
    {
      item->smith(1);
    }

    // Check the branch and the item to be created to determine how much
    // ammunition is created.
    ItemPtr component_item = creature->get_inventory()->get_from_base_id(ItemIdKeys::ITEM_ID_BRANCH);
    uint quantity = cic.calc_quantity(item, component_item);

    if (quantity > 0)
    {
      item->set_quantity(quantity);
    }

    // Now that we have no need for the branch, use it up.
    ItemManager im;
    im.remove_item_from_eq_or_inv(creature, ItemIdKeys::ITEM_ID_BRANCH);

    tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_FRONT);
  }

  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  manager.add_new_message(ActionTextKeys::get_fletchery_message(item->get_usage_description_sid()));
  manager.send();
}

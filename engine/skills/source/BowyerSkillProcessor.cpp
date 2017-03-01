#include "ActionTextKeys.hpp"
#include "BowyerSkillProcessor.hpp"
#include "CreateItemCalculator.hpp"
#include "CreateItemScreen.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"

using namespace std;

ActionCostValue BowyerSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = -1;

  if (creature != nullptr && map != nullptr)
  {
    if (check_for_bough(creature))
    {
      CurrentCreatureAbilities cca;

      if (cca.can_see(creature, true))
      {
        Game& game = Game::instance();
        DisplayPtr cur_disp = game.get_display();

        CreateItemScreen cis(cur_disp, SkillType::SKILL_GENERAL_BOWYER);
        string sel = cis.display();
        char sel_c = sel.at(0) - 'a';
        OptionPtr option = cis.get_option(sel_c);

        if (option != nullptr)
        {
          string item_base_id = option->get_external_id();
          create_bowyer_item(item_base_id, creature, map);

          acv = get_default_skill_action_cost_value(creature);
        }
      }
    }
  }

  return acv;
}

bool BowyerSkillProcessor::check_for_bough(CreaturePtr creature)
{
  bool has_bough = false;

  if (creature != nullptr)
  {
    ItemPtr bough = creature->get_inventory()->get_from_base_id(ItemIdKeys::ITEM_ID_BOUGH);

    if (bough != nullptr)
    {
      has_bough = true;
    }
  }

  if (has_bough == false)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_BOWYER_INSUFFICIENT_COMPONENTS));
    manager.send();
  }

  return has_bough;
}

void BowyerSkillProcessor::create_bowyer_item(const string& item_base_id, CreaturePtr creature, MapPtr map)
{
  // Remove the bough and create the item, adding a message about its
  // creation.
  ItemManager im;
  im.remove_item_from_eq_or_inv(creature, ItemIdKeys::ITEM_ID_BOUGH);
  ItemPtr item = ItemManager::create_item(item_base_id);
  TilePtr tile = MapUtils::get_tile_for_creature(map, creature);

  if (item != nullptr && tile != nullptr)
  {
    // Item's created.  Improve it appropriately.  Smith it
    // based on the improvement points;
    CreateItemCalculator cic;
    int potential_points = cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_BOWYER);
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

    tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_FRONT);
  }

  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  manager.add_new_message(ActionTextKeys::get_bowyer_message(item->get_usage_description_sid()));
  manager.send();
}
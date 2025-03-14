#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "FeatureProperties.hpp"
#include "FenceCalculator.hpp"
#include "FenceManipulator.hpp"
#include "Game.hpp"
#include "ItemManager.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"

using namespace std;

FenceManipulator::FenceManipulator(FeaturePtr feature)
: FeatureManipulator(feature)
{
}

void FenceManipulator::kick(CreaturePtr creature, MapPtr /*current_map*/, TilePtr feature_tile, const Coordinate& /*feature_coord*/, FeaturePtr feat)
{
  if (creature && creature->get_is_player())
  {
    FenceCalculator fc;
    IMessageManager& manager = MMF::instance();
    string msg_sid = ActionTextKeys::ACTION_FENCE_KICK_SLAT;

    if (RNG::percent_chance(fc.calc_pct_chance_break(creature)))
    {
      msg_sid = ActionTextKeys::ACTION_FENCE_BREAK_SLAT;
      feature_tile->remove_feature();

      ItemManager im;
      ItemPtr lumber = im.create_item(ItemIdKeys::ITEM_ID_LUMBER);
      feature_tile->get_items()->merge_or_add(lumber, InventoryAdditionType::INVENTORY_ADDITION_BACK);
    }
    else
    {
      bool slat_removed = String::to_bool(feat->get_additional_property(FeatureProperties::FEATURE_PROPERTIES_SLAT_REMOVED));

      if (RNG::percent_chance(fc.calc_pct_chance_board(creature)) && !slat_removed)
      {
        msg_sid = ActionTextKeys::ACTION_FENCE_BOARD_WITH_NAIL;
        feat->set_additional_property(FeatureProperties::FEATURE_PROPERTIES_SLAT_REMOVED, std::to_string(true));

        ItemManager im;
        ItemPtr board_with_nail_in_it = im.create_item(ItemIdKeys::ITEM_ID_BOARD_WITH_NAIL_IN_IT);
        feature_tile->get_items()->merge_or_add(board_with_nail_in_it, InventoryAdditionType::INVENTORY_ADDITION_BACK);
      }
    }

    manager.add_new_message(StringTable::get(msg_sid));
    manager.send();
  }
}

bool FenceManipulator::handle(TilePtr /*tile*/, CreaturePtr creature)
{
  if (creature != nullptr && creature->get_is_player())
  {
    IMessageManager& manager = MMF::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_FENCE_WOBBLE_POST));
    manager.send();
  }

  return false;
}

bool FenceManipulator::drop(CreaturePtr /*dropping_creature*/, TilePtr /*tile*/, ItemPtr /*item*/)
{
  return false;
}


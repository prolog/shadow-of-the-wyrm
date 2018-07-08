#include "SlotMachineManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "FeatureProperties.hpp"
#include "Game.hpp"
#include "ItemManager.hpp"
#include "ItemProperties.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SlotMachine.hpp"
#include "TextMessages.hpp"

using namespace std;

vector<string> SlotMachineManipulator::slot_faces = {};

SlotMachineManipulator::SlotMachineManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
  if (slot_faces.empty())
  {
    initialize();
  }
}

void SlotMachineManipulator::initialize()
{
  slot_faces = {"SLOT_MACHINE_FACE1",
                "SLOT_MACHINE_FACE2",
                "SLOT_MACHINE_FACE3",
                "SLOT_MACHINE_FACE4",
                "SLOT_MACHINE_FACE5"};
}

void SlotMachineManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_SLOT_MACHINE));
    manager.send();
  }
}

bool SlotMachineManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool slot_machine_used = false;
  Game& game = Game::instance();
  MapPtr current_map = game.get_current_map();

  if (tile != nullptr && creature != nullptr && creature->get_is_player() && feature != nullptr)
  {
    SlotMachinePtr slot = dynamic_pointer_cast<SlotMachine>(feature);

    if (slot != nullptr)
    {
      MapPtr current_map = Game::instance().get_current_map();
      vector<string> sf = slot_faces;
      uint cost = static_cast<uint>(slot->get_cost());
      int pct_chance_win = slot->get_pct_chance_win();
      float payout_multiplier = slot->get_payout_multiplier();
      uint win_amount = static_cast<uint>(cost * payout_multiplier);
      string sf1;
      string sf2;
      string sf3;

      string message = TextMessages::get_slot_machine_message(cost, pct_chance_win, win_amount);
      
      IMessageManager& manager = MM::instance();
      manager.add_new_confirmation_message(TextMessages::get_confirmation_message(message));
      bool play = creature->get_decision_strategy()->get_confirmation();

      if (play)
      {
        if (creature->get_inventory()->count_currency() > cost)
        {
          // Remove the necessary amount of ivory from the player.
          string outcome_sid = ActionTextKeys::ACTION_DEALER_LOSE_SID;
          ItemManager im;
          im.remove_item_from_eq_or_inv(creature, ItemIdKeys::ITEM_ID_CURRENCY, cost);

          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SLOT_MACHINE_USE));

          if (RNG::percent_chance(pct_chance_win))
          {
            ItemPtr winnings = ItemManager::create_item(ItemIdKeys::ITEM_ID_CURRENCY, win_amount);
            TilePtr creature_tile = MapUtils::get_tile_for_creature(current_map, creature);

            if (creature_tile != nullptr)
            {
              creature_tile->get_items()->merge_or_add(winnings, InventoryAdditionType::INVENTORY_ADDITION_BACK);
            }

            sf1 = sf2 = sf3 = sf.at(RNG::range(0, sf.size()-1));
            outcome_sid = ActionTextKeys::ACTION_DEALER_WIN_SID;
          }
          else
          {
            int idx = RNG::range(0, sf.size()-1);
            sf1 = sf.at(idx);
            
            sf.erase(sf.begin() + idx);

            idx = RNG::range(0, sf.size() - 1);
            sf2 = sf.at(idx);

            sf.erase(sf.begin() + idx);

            sf3 = sf.at(RNG::range(0, sf.size()-1));
          }

          manager.add_new_message(TextMessages::get_slot_machine_outcome_message(sf1, sf2, sf3));
          manager.add_new_message(StringTable::get(outcome_sid));
        }
        else
        {
          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SLOT_MACHINE_NSF));
        }

        manager.send();
      }

    }
  }

  return slot_machine_used;
}

bool SlotMachineManipulator::drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item)
{
  return false;
}

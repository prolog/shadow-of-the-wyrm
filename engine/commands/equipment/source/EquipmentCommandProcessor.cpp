#include "EquipmentCommandKeys.hpp"
#include "EquipmentCommandProcessor.hpp"
#include "EquipmentCommands.hpp"
#include "EquipmentTextKeys.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

EquipmentCommandProcessor::EquipmentCommandProcessor()
{
}

EquipmentCommandProcessor::~EquipmentCommandProcessor()
{
}

ActionCostValue EquipmentCommandProcessor::process(CreaturePtr creature, Command* command)
{
  ActionCostValue process_result = ActionCostConstants::DEFAULT;
  Game& game = Game::instance();
  
  if (creature && command)
  {
    EquipmentCommand* raw_eq_command = dynamic_cast<EquipmentCommand*>(command);
    
    if (raw_eq_command)
    {
      string command_name = raw_eq_command->get_name();
    
      if (raw_eq_command->is_wear_or_remove_command())
      {
        WearOrRemoveCommand* wear_raw_command = dynamic_cast<WearOrRemoveCommand*>(command);
        
        if (wear_raw_command)
        {
          EquipmentWornLocation worn_slot = wear_raw_command->get_equipment_worn_location();
          ItemPtr item_in_slot = creature->get_equipment().get_item(worn_slot);

          if (item_in_slot && item_in_slot->get_status() == ItemStatus::ITEM_STATUS_CURSED && creature->get_is_player())
          {
            process_result = 0;

            // Add an alert, as we're in a separate window.
            IMessageManager& manager = MM::instance();
            manager.alert(StringTable::get(EquipmentTextKeys::EQUIPMENT_REMOVAL_CURSED));
          }
          else
          {
            // Only advance the turn if something was actually either worn or removed.
            process_result = game.actions.wear_or_remove_item(creature, worn_slot);
          }          
        }
      }
      else if (command_name == EquipmentCommandKeys::CODEX)
      {
        EquipmentSlotCommand* esc = dynamic_cast<EquipmentSlotCommand*>(command);

        if (esc != nullptr)
        {
          EquipmentWornLocation ewl = esc->get_equipment_worn_location();
          Game::instance().get_action_manager_ref().item_codex(creature, ewl);
        }

        process_result = 0;
      }
      else if (command_name == EquipmentCommandKeys::YOUR_ITEMS)
      {
        list<IItemFilterPtr> display_filter = ItemFilterFactory::create_empty_filter();
        
        game.actions.inventory(creature, creature->get_inventory(), display_filter, {}, true, false);

        // Because the player is just looking at the items, this shouldn't
        // advance any turn information.
        process_result = 0;
      }
      else if (command_name == EquipmentCommandKeys::EXIT_EQUIPMENT)
      {
        process_result = -1;
      }
    }
  }
      
  return process_result;
}

pair<bool, ItemPtr> EquipmentCommandProcessor::process_selection(CreaturePtr creature, Command* command)
{
  pair<bool, ItemPtr> selection = { false, nullptr };
  Game& game = Game::instance();

  if (creature && command)
  {
    EquipmentCommand* raw_eq_command = dynamic_cast<EquipmentCommand*>(command);

    if (raw_eq_command)
    {
      string command_name = raw_eq_command->get_name();

      if (raw_eq_command->is_wear_or_remove_command())
      {
        WearOrRemoveCommand* wear_raw_command = dynamic_cast<WearOrRemoveCommand*>(command);

        if (wear_raw_command)
        {
          EquipmentWornLocation worn_slot = wear_raw_command->get_equipment_worn_location();
          ItemPtr item_in_slot = creature->get_equipment().get_item(worn_slot);

          if (item_in_slot)
          {
            selection.first = true;
            selection.second = item_in_slot;
          }
        }
      }
      // In selection mode, allow the codex to be shown, but don't set the
      // return value to true - this will allow the user to look at items
      // in codex mode and then select items after.
      else if (command_name == EquipmentCommandKeys::CODEX)
      {
        EquipmentSlotCommand* esc = dynamic_cast<EquipmentSlotCommand*>(command);

        if (esc != nullptr)
        {
          EquipmentWornLocation ewl = esc->get_equipment_worn_location();
          Game::instance().get_action_manager_ref().item_codex(creature, ewl);
        }
      }
      else if (command_name == EquipmentCommandKeys::YOUR_ITEMS)
      {
        list<IItemFilterPtr> display_filter = ItemFilterFactory::create_empty_filter();

        // When processing the inventory for selection, we don't want it
        // read-only (first boolean), because we want to select items
        // and possibly return those back.
        ItemPtr inv_item = game.actions.inventory(creature, creature->get_inventory(), display_filter, {}, false, false);

        if (inv_item != nullptr)
        {
          selection.first = true;
          selection.second = inv_item;
        }
      }
      else if (command_name == EquipmentCommandKeys::EXIT_EQUIPMENT)
      {
        selection.first = true;
      }
    }
  }

  return selection;
}

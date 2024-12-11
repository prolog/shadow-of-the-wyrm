#include "CurrentCreatureAbilities.hpp"
#include "EquipmentCommandFactory.hpp"
#include "EquipmentCommandProcessor.hpp"
#include "EquipmentKeyboardCommandMap.hpp"
#include "EquipmentManager.hpp"
#include "EquipmentScreen.hpp"
#include "EquipmentTranslator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ItemIdentifier.hpp"
#include "ItemManager.hpp"
#include "MessageManagerFactory.hpp"
#include "TextMessages.hpp"

using namespace std;

EquipmentManager::EquipmentManager(DisplayPtr new_display, CreaturePtr new_creature)
: display(new_display), creature(new_creature)
{
}

EquipmentManager::~EquipmentManager()
{
}

// Do the actual equipment management, interfacing with the UI as needed.
ActionCostValue EquipmentManager::manage_equipment()
{
  ActionCostValue total_action_cost = ActionCostConstants::NO_ACTION;
  ActionCostValue action_cost = ActionCostConstants::NO_ACTION; // Looking at eq has no cost - adding or removing items will update this.
  ulonglong screens_created = 0;
  
  bool manage_eq = true; // For looping

  try
  {
    if (creature)
    {
      CommandFactoryPtr command_factory    = std::make_unique<EquipmentCommandFactory>();
      KeyboardCommandMapPtr kb_command_map = std::make_unique<EquipmentKeyboardCommandMap>();
    
      while (manage_eq)
      {
        if (display && creature->get_is_player())
        {
          EquipmentScreen es(display, creature);
          string screen_selection = es.display();

          if (!screen_selection.empty())
          {
            CommandPtr equipment_command = command_factory->create(screen_selection.at(0), kb_command_map->get_command_type(screen_selection));
            action_cost = EquipmentCommandProcessor::process(creature, equipment_command.get());

            if ((action_cost > 0) && (total_action_cost == 0))
            {
              total_action_cost = action_cost;
            }
          }
        }
        else
        {
          manage_eq = 0;
        }
      
        // -1 is a special value for the equipment command.  "0" means "don't advance the turn,
        // but keep the equipment screen up."  "-1" means "exit was selected."
        if (action_cost == -1)
        {
          manage_eq = 0;
        }
      }    
    }
  }
  catch(...)
  {
  }

  if (creature->get_is_player())
  {
    for (ulonglong i = 0; i < screens_created; i++)
    {
      display->clear_screen();
    }
  }

  return total_action_cost;
}

ActionCostValue EquipmentManager::equip(CreaturePtr creature, ItemPtr i, const EquipmentWornLocation ewl)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr && i != nullptr)
  {
    Game& game = Game::instance();
    CreaturePtr player = game.get_current_player();

    ItemManager im;
    acv = im.equip(creature, i, ewl);

    // Add a message about equipping.
    CurrentCreatureAbilities cca;
    bool player_blind = cca.can_see(player) == false;

    if (player != nullptr && !player_blind)
    {
      ItemIdentifier iid;
      IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, GameUtils::is_creature_in_player_view_map(game, creature->get_id()));
      string msg = TextMessages::get_equip_message(creature->get_description_sid(), iid.get_appropriate_usage_description(i));
      manager.add_new_message(msg);
      manager.send();
    }
  }

  return acv;
}

ItemPtr EquipmentManager::select_item()
{
  ItemPtr item;

  if (creature != nullptr)
  {
    bool eq_loop = true;

    CommandFactoryPtr command_factory = std::make_unique<EquipmentCommandFactory>();
    KeyboardCommandMapPtr kb_command_map = std::make_unique<EquipmentKeyboardCommandMap>();

    while (eq_loop)
    {
      EquipmentScreen es(display, creature);
      string screen_selection = es.display();

      if (!screen_selection.empty())
      {
        CommandPtr equipment_command = command_factory->create(screen_selection.at(0), kb_command_map->get_command_type(screen_selection));

        pair<bool, ItemPtr> selection = EquipmentCommandProcessor::process_selection(creature, equipment_command.get());

        if (selection.first)
        {
          eq_loop = false;
          item = selection.second;
        }
      }
    }
  }

  return item;
}

ActionCostValue EquipmentManager::get_action_cost_value(CreaturePtr /* creature */) const
{
  return 1;
}

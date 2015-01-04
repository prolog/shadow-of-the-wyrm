#include "ActionManager.hpp"
#include "ClassManager.hpp"
#include "InitialItemEquipper.hpp"
#include "InitialItemSelector.hpp"
#include "ItemManager.hpp"

using namespace std;

void InitialItemEquipper::equip(CreaturePtr creature, ActionManager& am)
{
  if (creature)
  {
    ClassManager cm;
    InitialItemSelector iis;
    string creature_race = creature->get_race_id();
    ClassPtr current_class = cm.get_class(creature->get_class_id());
    
    if (current_class)
    {
      map<EquipmentWornLocation, InitialItem> initial_item_map = current_class->get_initial_equipment();
      
      for (const InitialEquipmentMap::value_type& ii_i : initial_item_map)
      {
        InitialItem ii = ii_i.second;
        pair<string, uint> item_details = iis.get_item_details(creature_race, ii);
        string item_id = item_details.first;
        uint item_quantity = item_details.second;
        
        if (!item_id.empty())
        {
          ItemPtr item = ItemManager::create_item(item_id, item_quantity);
          item->set_quantity(item_quantity);
          
          Equipment& eq = creature->get_equipment();
          if (item->get_quantity() > 1 && !eq.can_equip_multiple_items(ii_i.first))
          {
            // Sanity check: only allow multiple items for slots that allow this.
            item->set_quantity(1); 
          }
          
          am.handle_item(creature, ItemAction::ITEM_ACTION_EQUIP, item);
        }
      }
    }  
  }
}

// Create the creature's inventory based on the items specified in its class.
void InitialItemEquipper::add_inventory_items(CreaturePtr creature, ActionManager& am)
{
  if (creature)
  {
    ClassManager cm;
    InitialItemSelector iis;
    string creature_race = creature->get_race_id();
    ClassPtr current_class = cm.get_class(creature->get_class_id());
    
    if (current_class)
    {
      vector<InitialItem> vii = current_class->get_initial_inventory();

      for (const InitialItem& ii : vii)
      {
        pair<string, uint> item_details = iis.get_item_details(creature_race, ii);
        string item_id = item_details.first;
        uint item_quantity = item_details.second;
        
        if (!item_id.empty())
        {
          am.handle_item(creature, ItemAction::ITEM_ACTION_PICK_UP, ItemManager::create_item(item_id, item_quantity));
        }
      }
    }
  }
}


#include <boost/foreach.hpp>
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
      
      BOOST_FOREACH(InitialEquipmentMap::value_type& ii_i, initial_item_map)
      {
        InitialItem ii = ii_i.second;
        string item_id = iis.get_item_id(creature_race, ii);
        
        if (!item_id.empty())
        {
          am.handle_item(creature, ITEM_ACTION_EQUIP, ItemManager::create_item(item_id));
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

      BOOST_FOREACH(InitialItem& ii, vii)
      {
        string item_id = iis.get_item_id(creature_race, ii);
        
        if (!item_id.empty())
        {
          am.handle_item(creature, ITEM_ACTION_PICK_UP, ItemManager::create_item(item_id));
        }
      }
    }
  }
}


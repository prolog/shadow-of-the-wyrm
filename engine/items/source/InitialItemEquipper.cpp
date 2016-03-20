#include "ActionManager.hpp"
#include "ClassManager.hpp"
#include "InitialItemEquipper.hpp"
#include "InitialItemSelector.hpp"
#include "ItemManager.hpp"

using namespace std;

void InitialItemEquipper::equip(CreaturePtr creature, const CreatureGenerationValues& cgv, ActionManager& am)
{
  if (creature)
  {
    ClassManager cm;
    ClassPtr current_class = cm.get_class(creature->get_class_id());
    vector<map<EquipmentWornLocation, InitialItem>> equipment_maps;

    if (current_class)
    {
      equipment_maps.push_back(current_class->get_initial_equipment());
    }

    equipment_maps.push_back(cgv.get_initial_equipment());

    for (const auto& map : equipment_maps)
    {
      process_initial_equipment(creature, map, am);
    }
  }
}

// Equip an initial equipment map, whether from the class, the creature's
// definition, or something else.
void InitialItemEquipper::process_initial_equipment(CreaturePtr creature, const map<EquipmentWornLocation, InitialItem>& initial_equipment_map, ActionManager& am)
{
  if (creature != nullptr)
  {
    InitialItemSelector iis;
    string creature_race = creature->get_race_id();

    for (const InitialEquipmentMap::value_type& ii_i : initial_equipment_map)
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

        am.handle_item(creature, ItemAction::ITEM_ACTION_EQUIP, item, ii_i.first);
      }
    }
  }
}

// Create the creature's inventory based on the items specified in its class.
void InitialItemEquipper::add_inventory_items(CreaturePtr creature, const CreatureGenerationValues& cgv, ActionManager& am)
{
  if (creature)
  {
    ClassManager cm;
    string creature_race = creature->get_race_id();
    ClassPtr current_class = cm.get_class(creature->get_class_id());
    vector<vector<InitialItem>> initial_inventories;
    
    if (current_class)
    {
      initial_inventories.push_back(current_class->get_initial_inventory());
    }

    initial_inventories.push_back(cgv.get_initial_inventory());

    for (const auto& inv : initial_inventories)
    {
      process_initial_inventory(creature, inv, am);
    }
  }
}

// Process an initial inventory, adding the items to the creature's inventory.
void InitialItemEquipper::process_initial_inventory(CreaturePtr creature, const vector<InitialItem>& initial_inventory, ActionManager& am)
{
  if (creature != nullptr)
  {
    for (const InitialItem& ii : initial_inventory)
    {
      InitialItemSelector iis;
      string creature_race = creature->get_race_id();
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


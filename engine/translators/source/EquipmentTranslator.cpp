#include <boost/foreach.hpp>
#include "CurrentCreatureAbilities.hpp"
#include "EquipmentTranslator.hpp"
#include "ItemTranslator.hpp"

EquipmentTranslator::EquipmentTranslator()
{
}

EquipmentTranslator::~EquipmentTranslator()
{
}

// Create display items for each item in the creature's equipment.
DisplayEquipmentMap EquipmentTranslator::create_display_equipment(const CreaturePtr& c)
{
  DisplayEquipmentMap display_equipment;
  CurrentCreatureAbilities cca;

  if (c)
  {
    Equipment eq = c->get_equipment();
    EquipmentMap raw_eq = eq.get_equipment();
    
    for (EquipmentMap::const_iterator e_it = raw_eq.begin(); e_it != raw_eq.end(); e_it++)
    {
      EquipmentWornLocation worn_location = e_it->first;
      ItemPtr equipped_item = e_it->second;
      
      DisplayItem display_item = ItemTranslator::create_display_item(!cca.can_see(c), equipped_item);
      
      display_equipment[worn_location] = display_item;
    }
  }

  return display_equipment;
}

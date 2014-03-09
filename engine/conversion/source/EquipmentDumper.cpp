#include <sstream>
#include "Conversion.hpp"
#include "EquipmentDumper.hpp"
#include "ItemDumper.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "StringTable.hpp"

using namespace std;

EquipmentDumper::EquipmentDumper(CreaturePtr new_creature, const uint new_num_cols)
: creature(new_creature), num_cols(new_num_cols)
{
}

string EquipmentDumper::str() const
{
  ostringstream ss;
  
  ss << String::centre(StringTable::get(TextKeys::EQUIPMENT), num_cols) << endl << endl;
  ss << get_equipment() << endl << endl;
  
  return ss.str();
}

string EquipmentDumper::get_equipment() const
{
  ostringstream ss;

  if (creature)
  {
    EquipmentMap equipment = creature->get_equipment().get_equipment();
    
    for (EquipmentMap::const_iterator e_it = equipment.begin(); e_it != equipment.end(); e_it++)
    {
      ItemDumper id(creature, e_it->second, true);
      string item_desc = id.str();
      ss << TextMessages::get_equipment_location(e_it->first) << ": " << item_desc << endl;

      if (item_desc.empty())
      {
        // Ensure there's always a second line for extra desc, even if 
        // nothing is equipped.
        ss << endl; 
      }
    }
  }

  return ss.str();
}

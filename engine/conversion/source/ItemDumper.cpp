#include <sstream>
#include "CurrentCreatureAbilities.hpp"
#include "DisplayItem.hpp"
#include "EquipmentTextKeys.hpp"
#include "ItemDumper.hpp"
#include "ItemIdentifier.hpp"
#include "ItemTranslator.hpp"
#include "StringTable.hpp"

using namespace std;

ItemDumper::ItemDumper(CreaturePtr new_creature, ItemPtr new_item, bool show_additional_desc)
: creature(new_creature), item(new_item), show_addl_desc(show_additional_desc), ignore_blindness_checks(false)
{
}

void ItemDumper::set_ignore_blindness_checks(const bool new_ignore_checks)
{
  ignore_blindness_checks = new_ignore_checks;
}

bool ItemDumper::get_ignore_blindness_checks() const
{
  return ignore_blindness_checks;
}

string ItemDumper::str() const
{
  ostringstream ss;
  CurrentCreatureAbilities cca;

  if (item)
  {
    bool is_blind = !cca.can_see(creature);

    if (ignore_blindness_checks || creature->is_dead())
    {
      is_blind = false;
    }

    DisplayItem display_item = ItemTranslator::create_display_item(is_blind, item);

    ss << display_item.get_description() << endl;
    string additional_desc = display_item.get_additional_description();

    if (show_addl_desc)
    {
      if (!additional_desc.empty())
      {
        ss << StringTable::get(EquipmentTextKeys::EQUIPMENT_RESISTS_FLAGS) << ": " << additional_desc << endl;
      }

      ss << endl;
    }
  }
  else
  {
    ss << "-" << endl << endl;
  }

  // This may be empty - that's fine if we've passed in a null ItemPtr.
  return ss.str();
}
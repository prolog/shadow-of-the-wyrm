#include <sstream>
#include "CurrentCreatureAbilities.hpp"
#include "DisplayItem.hpp"
#include "ItemDumper.hpp"
#include "ItemIdentifier.hpp"
#include "ItemTranslator.hpp"
#include "ResistanceTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

ItemDumper::ItemDumper(CreaturePtr new_creature, ItemPtr new_item, bool show_additional_desc)
: creature(new_creature), item(new_item), show_addl_desc(show_additional_desc)
{
}

string ItemDumper::str() const
{
  ostringstream ss;
  CurrentCreatureAbilities cca;

  if (item)
  {
    DisplayItem display_item = ItemTranslator::create_display_item(!cca.can_see(creature), item);

    ss << display_item.get_description() << endl;
    string additional_desc = display_item.get_additional_description();

    if (show_addl_desc)
    {
      if (!additional_desc.empty())
      {
        ss << StringTable::get(ResistanceTextKeys::RESISTANCES_ABRV) << ": " << additional_desc << endl;
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
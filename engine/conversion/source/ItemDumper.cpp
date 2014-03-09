#include <sstream>
#include "CurrentCreatureAbilities.hpp"
#include "DisplayItem.hpp"
#include "ItemDumper.hpp"
#include "ItemIdentifier.hpp"
#include "ItemTranslator.hpp"
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

    if (show_addl_desc)
    {
      ss << display_item.get_additional_description();
    }
  }
  else
  {
    ss << "-";
  }

  // This may be empty - that's fine if we've passed in a null ItemPtr.
  return ss.str();
}
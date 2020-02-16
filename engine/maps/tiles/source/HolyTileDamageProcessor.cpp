#include "HolyTileDamageProcessor.hpp"
#include "TileTextKeys.hpp"

using namespace std;

// Divine powers can curse anything.
bool HolyTileDamageProcessor::affects_item(ItemPtr item)
{
  return true;
}

string HolyTileDamageProcessor::get_message_sid() const
{
  string message_sid = TileTextKeys::TILE_DAMAGE_HOLY;
  return message_sid;
}

int HolyTileDamageProcessor::get_pct_chance() const
{
  return 50;
}
  
bool HolyTileDamageProcessor::destroy_item() const
{
  return false;
}

// The Nine are jerks
// Their wrath is rough
// You call on them
// They curse your stuff
void HolyTileDamageProcessor::process_item(ItemPtr item)
{
  if (item != nullptr)
  {
    item->set_status(ItemStatus::ITEM_STATUS_CURSED);
    item->set_status_identified(true);
  }
}

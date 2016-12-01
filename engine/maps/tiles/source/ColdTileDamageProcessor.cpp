#include "ColdTileDamageProcessor.hpp"
#include "TileTextKeys.hpp"

using namespace std;

// Glass shatters under magical cold.
bool ColdTileDamageProcessor::affects_item(ItemPtr item)
{
  bool aff = false;

  if (item != nullptr)
  {
    aff = (item->get_material_type() == MaterialType::MATERIAL_TYPE_GLASS);
  }

  return aff;
}

string ColdTileDamageProcessor::get_message_sid() const
{
  string message_sid = TileTextKeys::TILE_DAMAGE_COLD;
  return message_sid;
}

int ColdTileDamageProcessor::get_pct_chance() const
{
  return 30;
}
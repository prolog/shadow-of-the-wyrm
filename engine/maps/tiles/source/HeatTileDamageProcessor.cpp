#include "HeatTileDamageProcessor.hpp"
#include "TileTextKeys.hpp"

using namespace std;

// Paper, wood, and plant fibers burn.
bool HeatTileDamageProcessor::affects_item(ItemPtr item)
{
  bool aff = false;

  if (item != nullptr)
  {
    MaterialType mt = item->get_material_type();

    aff = mt == MaterialType::MATERIAL_TYPE_CLOTH ||
          mt == MaterialType::MATERIAL_TYPE_PAPER ||
          mt == MaterialType::MATERIAL_TYPE_WOOD;
  }

  return aff;
}

string HeatTileDamageProcessor::get_message_sid() const
{
  string message_sid = TileTextKeys::TILE_DAMAGE_HEAT;
  return message_sid;
}

int HeatTileDamageProcessor::get_pct_chance() const
{
  return 30;
}

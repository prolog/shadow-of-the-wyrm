#include "ArcaneTileDamageProcessor.hpp"
#include "ItemEnchantmentCalculator.hpp"
#include "RNG.hpp"
#include "TileTextKeys.hpp"

using namespace std;

ArcaneTileDamageProcessor::ArcaneTileDamageProcessor()
: cur_message_sid(TileTextKeys::TILE_DAMAGE_ARCANE), destroy(true)
{
}

bool ArcaneTileDamageProcessor::affects_item(ItemPtr item)
{
  if (item != nullptr && item->can_enchant())
  {
    return true;
  }

  return false;
}

string ArcaneTileDamageProcessor::get_message_sid() const
{
  return cur_message_sid;
}

int ArcaneTileDamageProcessor::get_pct_chance() const
{
  return 30;
}

bool ArcaneTileDamageProcessor::destroy_item() const
{
  return destroy;
}

void ArcaneTileDamageProcessor::process_item(ItemPtr item)
{
  if (item != nullptr)
  {
    // Magics are unstable. They might destroy an item outright, but also
    // have a chance of enchanting it.
    if (RNG::percent_chance(50))
    {
      destroy = true;
      cur_message_sid = TileTextKeys::TILE_DAMAGE_ARCANE;
    }
    else
    {
      destroy = false;
      cur_message_sid = TileTextKeys::TILE_DAMAGE_ARCANE_ENCHANT;
    }

    if (destroy == false)
    {
      ItemEnchantmentCalculator iec;
      float enchant_mult = 1.0f;
      int pct_chance_brand = iec.calculate_pct_chance_brand(enchant_mult, item);
      item->enchant(pct_chance_brand, enchant_mult);
    }
  }
}
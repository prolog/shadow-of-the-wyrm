#include "AcidTileDamageProcessor.hpp"
#include "TileTextKeys.hpp"

using namespace std;

// Assumption that everything uses really, really strong acid, which can
// dissolve anything.
bool AcidTileDamageProcessor::affects_item(ItemPtr /*item*/)
{
  return true;
}

string AcidTileDamageProcessor::get_message_sid() const
{
  string message_sid = TileTextKeys::TILE_DAMAGE_ACID;
  return message_sid;
}

int AcidTileDamageProcessor::get_pct_chance() const
{
  return 50;
}

#include "PoisonTileDamageProcessor.hpp"
#include "Consumable.hpp"
#include "TileTextKeys.hpp"

using namespace std;

// Food and drink can spoil
bool PoisonTileDamageProcessor::affects_item(ItemPtr item)
{
  bool aff = false;

  ConsumablePtr consum = std::dynamic_pointer_cast<Consumable>(item);

  if (consum != nullptr)
  {
    aff = true;
  }

  return aff;
}

// Poison doesn't affect general material types, which are checked in the
// top-level affects_feature function.
bool PoisonTileDamageProcessor::affects_material(const MaterialType /*mt*/)
{
  return false;
}

string PoisonTileDamageProcessor::get_message_sid() const
{
  string message_sid = TileTextKeys::TILE_DAMAGE_POISON;
  return message_sid;
}

int PoisonTileDamageProcessor::get_pct_chance() const
{
  return 60;
}

bool PoisonTileDamageProcessor::destroy_item() const
{
  return false;
}

void PoisonTileDamageProcessor::process_item(ItemPtr item)
{
  ConsumablePtr consum = std::dynamic_pointer_cast<Consumable>(item);

  if (consum != nullptr)
  {
    consum->set_poisoned(true);
  }
}

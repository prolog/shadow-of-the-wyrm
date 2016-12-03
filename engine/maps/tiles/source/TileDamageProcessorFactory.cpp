#include "TileDamageProcessorFactory.hpp"
#include "ColdTileDamageProcessor.hpp"
#include "NullTileDamageProcessor.hpp"
#include "PoisonTileDamageProcessor.hpp"

using namespace std;

TileDamageProcessorPtr TileDamageProcessorFactory::create_tile_damage_processor(const DamageType dt)
{
  TileDamageProcessorPtr dam_proc;

  switch (dt)
  {
    case DamageType::DAMAGE_TYPE_COLD:
      dam_proc = std::make_shared<ColdTileDamageProcessor>();
      break;
    case DamageType::DAMAGE_TYPE_POISON:
      dam_proc = std::make_shared<PoisonTileDamageProcessor>();
      break;
    case DamageType::DAMAGE_TYPE_SLASH:
    case DamageType::DAMAGE_TYPE_PIERCE:
    case DamageType::DAMAGE_TYPE_POUND:
    case DamageType::DAMAGE_TYPE_HEAT:
    case DamageType::DAMAGE_TYPE_ACID:
    case DamageType::DAMAGE_TYPE_HOLY:
    case DamageType::DAMAGE_TYPE_SHADOW:
    case DamageType::DAMAGE_TYPE_ARCANE:
    case DamageType::DAMAGE_TYPE_LIGHTNING:
    default:
      dam_proc = std::make_shared<NullTileDamageProcessor>();
      break;
  }

  return dam_proc;
}

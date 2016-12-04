#include "TileDamageProcessorFactory.hpp"
#include "AcidTileDamageProcessor.hpp"
#include "ColdTileDamageProcessor.hpp"
#include "HeatTileDamageProcessor.hpp"
#include "NullTileDamageProcessor.hpp"
#include "PoisonTileDamageProcessor.hpp"

using namespace std;

TileDamageProcessorPtr TileDamageProcessorFactory::create_tile_damage_processor(const DamageType dt)
{
  TileDamageProcessorPtr dam_proc;

  switch (dt)
  {
    case DamageType::DAMAGE_TYPE_HEAT:
      dam_proc = std::make_shared<HeatTileDamageProcessor>();
      break;
    case DamageType::DAMAGE_TYPE_COLD:
      dam_proc = std::make_shared<ColdTileDamageProcessor>();
      break;
    case DamageType::DAMAGE_TYPE_POISON:
      dam_proc = std::make_shared<PoisonTileDamageProcessor>();
      break;
    case DamageType::DAMAGE_TYPE_ACID:
      dam_proc = std::make_shared<AcidTileDamageProcessor>();
      break;
    case DamageType::DAMAGE_TYPE_SLASH:
    case DamageType::DAMAGE_TYPE_PIERCE:
    case DamageType::DAMAGE_TYPE_POUND:
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

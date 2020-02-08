#include "TileDamageProcessorFactory.hpp"
#include "AcidTileDamageProcessor.hpp"
#include "ArcaneTileDamageProcessor.hpp"
#include "ColdTileDamageProcessor.hpp"
#include "HeatTileDamageProcessor.hpp"
#include "HolyTileDamageProcessor.hpp"
#include "NullTileDamageProcessor.hpp"
#include "PoisonTileDamageProcessor.hpp"

using namespace std;

TileDamageProcessorPtr TileDamageProcessorFactory::create_tile_damage_processor(const DamageType dt)
{
  TileDamageProcessorPtr dam_proc;
  
  switch (dt)
  {
    case DamageType::DAMAGE_TYPE_HEAT:
      dam_proc = std::make_unique<HeatTileDamageProcessor>();
      break;
    case DamageType::DAMAGE_TYPE_COLD:
      dam_proc = std::make_unique<ColdTileDamageProcessor>();
      break;
    case DamageType::DAMAGE_TYPE_POISON:
      dam_proc = std::make_unique<PoisonTileDamageProcessor>();
      break;
    case DamageType::DAMAGE_TYPE_ACID:
      dam_proc = std::make_unique<AcidTileDamageProcessor>();
      break;
    case DamageType::DAMAGE_TYPE_HOLY:
      dam_proc = std::make_unique<HolyTileDamageProcessor>();
      break;
    case DamageType::DAMAGE_TYPE_ARCANE:
      dam_proc = std::make_unique<ArcaneTileDamageProcessor>();
      break;
    case DamageType::DAMAGE_TYPE_SLASH:
    case DamageType::DAMAGE_TYPE_PIERCE:
    case DamageType::DAMAGE_TYPE_POUND:
    case DamageType::DAMAGE_TYPE_SHADOW:
    case DamageType::DAMAGE_TYPE_LIGHTNING:
    default:
      dam_proc = std::make_unique<NullTileDamageProcessor>();
      break;
  }

  return dam_proc;
}

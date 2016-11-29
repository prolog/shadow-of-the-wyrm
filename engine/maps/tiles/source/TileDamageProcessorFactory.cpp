#include "TileDamageProcessorFactory.hpp"
#include "NullTileDamageProcessor.hpp"

using namespace std;

TileDamageProcessorPtr TileDamageProcessorFactory::create_tile_damage_processor(const DamageType dt)
{
  TileDamageProcessorPtr dam_proc = std::make_shared<NullTileDamageProcessor>();

  return dam_proc;
}

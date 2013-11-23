#include "GraveyardGeneratorFactory.hpp"
#include "OrderedGraveyardGenerator.hpp"
#include "ScatteredGraveyardGenerator.hpp"

using std::string;

GraveyardGeneratorFactory::GraveyardGeneratorFactory()
{
}

GraveyardGeneratorFactory::~GraveyardGeneratorFactory()
{
}

// Create an ordered graveyard (graves in nice rows)
GeneratorPtr GraveyardGeneratorFactory::create_ordered_graveyard_generator(const string& map_exit_id, const bool include_tomb)
{
  GeneratorPtr ordered_gen = std::make_shared<OrderedGraveyardGenerator>(map_exit_id);
  return ordered_gen;
}

// Create a scattered graveyard (graves placed randomly)
GeneratorPtr GraveyardGeneratorFactory::create_scattered_graveyard_generator(const string& map_exit_id, const bool include_tomb)
{
  GeneratorPtr scattered_gen = std::make_shared<ScatteredGraveyardGenerator>(map_exit_id);
  return scattered_gen;
}

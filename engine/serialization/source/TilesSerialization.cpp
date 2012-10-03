#include "MapRegistry.hpp"
#include "TilesSerialization.hpp"

void TilesSerialization::save(std::ostream& stream, MapRegistry& registry)
{
}

SerializationReturnCode TilesSerialization::load()
{
  return SERIALIZATION_OK;
}


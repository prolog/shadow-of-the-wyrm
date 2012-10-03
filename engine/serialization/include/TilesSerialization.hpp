#pragma once
#include <ostream>
#include "SerializationTypes.hpp"

class MapRegistry;

class TilesSerialization
{
  public:
    static void save(std::ostream& stream, MapRegistry& registry);
    static SerializationReturnCode load();
};

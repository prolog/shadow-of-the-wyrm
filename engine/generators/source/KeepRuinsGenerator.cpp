#include "KeepRuinsGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"

using std::string;

KeepRuinsGenerator::KeepRuinsGenerator(MapPtr new_base_map)
: KeepGenerator(new_base_map, 10)
{
}


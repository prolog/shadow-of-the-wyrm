#include "ChurchGenerator.hpp"

ChurchGenerator::ChurchGenerator(const std::string& new_deity_id, MapPtr new_base_map, const TileType church_type) 
: Generator(new_base_map->get_map_exit_id(), church_type)
, deity_id(new_deity_id)
, base_map(new_base_map)
{
}



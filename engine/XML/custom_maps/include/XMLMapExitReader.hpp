#pragma once
#include "Map.hpp"
#include "XMLDataStructures.hpp"

// A class for reading in map exits on custom maps.
class XMLMapExitReader
{
  public:
    void parse_exits(const XMLNode& exits_node, MapPtr map);
    void parse_exit(const XMLNode& exit_node, MapPtr map);    
};


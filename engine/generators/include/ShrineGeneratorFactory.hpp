#pragma once
#include "Generator.hpp"

enum struct ShrineLayoutType
{
  SHRINE_LAYOUT_RECTANGULAR = 0,
  SHRINE_LAYOUT_CROSS = 1
};

// Shrine generators work like village generators, in that they generate 
// shrines on top of another base map, like a field or forest.
class ShrineGeneratorFactory
{
  public:
    static GeneratorPtr create_random_shrine_generator(MapPtr shrine_base_map);

    static GeneratorPtr create_rectangular_shrine_generator(MapPtr shrine_base_map);
    static GeneratorPtr create_cross_shrine_generator(MapPtr shrine_base_map);
};


#include "CrossShrineGenerator.hpp"
#include "RectangularShrineGenerator.hpp"
#include "ShrineGeneratorFactory.hpp"
#include "RNG.hpp"

using namespace std;

GeneratorPtr ShrineGeneratorFactory::create_random_shrine_generator(MapPtr base_map)
{
  GeneratorPtr shrine_generator;

  ShrineLayoutType shrine_layout = static_cast<ShrineLayoutType>(RNG::range(static_cast<int>(ShrineLayoutType::SHRINE_LAYOUT_RECTANGULAR), static_cast<int>(ShrineLayoutType::SHRINE_LAYOUT_RECTANGULAR)));

  switch(shrine_layout)
  {
    case ShrineLayoutType::SHRINE_LAYOUT_RECTANGULAR:
      shrine_generator = create_rectangular_shrine_generator(base_map);
      break;
    case ShrineLayoutType::SHRINE_LAYOUT_CROSS:
    default:
      shrine_generator = create_cross_shrine_generator(base_map);
      break;
  }

  return shrine_generator;
}

GeneratorPtr ShrineGeneratorFactory::create_rectangular_shrine_generator(MapPtr base_map)
{
  GeneratorPtr shrine = make_shared<RectangularShrineGenerator>(base_map);
  return shrine;
}

GeneratorPtr ShrineGeneratorFactory::create_cross_shrine_generator(MapPtr base_map)
{
  GeneratorPtr shrine = make_shared<CrossShrineGenerator>(base_map);
  return shrine;
}
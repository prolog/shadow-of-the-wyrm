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
    default:
      shrine_generator = create_rectangular_shrine_generator(base_map);
      break;
  }

  return shrine_generator;
}

GeneratorPtr ShrineGeneratorFactory::create_rectangular_shrine_generator(MapPtr base_map)
{
  GeneratorPtr shrine = make_shared<RectangularShrineGenerator>(base_map);
  return shrine;
}

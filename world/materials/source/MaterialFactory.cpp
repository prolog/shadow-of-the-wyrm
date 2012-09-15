#include <boost/make_shared.hpp>
#include "MaterialFactory.hpp"
#include "Cloth.hpp"
#include "DragonScale.hpp"
#include "Glass.hpp"
#include "Iron.hpp"
#include "Ivory.hpp"
#include "Leather.hpp"
#include "Marble.hpp"
#include "Onyx.hpp"
#include "Paper.hpp"
#include "Steel.hpp"
#include "Stone.hpp"
#include "Wood.hpp"

using boost::make_shared;

MaterialFactory::MaterialFactory()
{
}

MaterialFactory::~MaterialFactory()
{
}

MaterialPtr MaterialFactory::create_material(const MaterialType type)
{
  MaterialPtr material;

  switch(type)
  {
    case MATERIAL_TYPE_CLOTH:
      material = make_shared<Cloth>();
      break;
    case MATERIAL_TYPE_DRAGON_SCALE:
      material = make_shared<DragonScale>();
      break;
    case MATERIAL_TYPE_GLASS:
      material = make_shared<Glass>();
      break;
    case MATERIAL_TYPE_IRON:
      material = make_shared<Iron>();
      break;
    case MATERIAL_TYPE_LEATHER:
      material = make_shared<Leather>();
      break;
    case MATERIAL_TYPE_PAPER:
      material = make_shared<Paper>();
      break;
    case MATERIAL_TYPE_STEEL:
      material = make_shared<Steel>();
      break;
    case MATERIAL_TYPE_STONE:
      material = make_shared<Stone>();
      break;
    case MATERIAL_TYPE_WOOD:
      material = make_shared<Wood>();
      break;
    case MATERIAL_TYPE_MARBLE:
      material = make_shared<Marble>();
      break;
    case MATERIAL_TYPE_ONYX:
      material = make_shared<Onyx>();
      break;
    case MATERIAL_TYPE_IVORY:
      material = make_shared<Ivory>();
      break;
    default:
      material = make_shared<Wood>();
      break;
  }

  return material;
}

// JCD FIXME: Unit tests to ensure that the type of the
// created material matches the input type.
#ifdef UNIT_TESTS
#include "unit_tests/MaterialFactory_test.cpp"
#endif

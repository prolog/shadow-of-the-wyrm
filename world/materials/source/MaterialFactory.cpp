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

using namespace std;

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
      material = boost::make_shared<Cloth>();
      break;
    case MATERIAL_TYPE_DRAGON_SCALE:
      material = boost::make_shared<DragonScale>();
      break;
    case MATERIAL_TYPE_GLASS:
      material = boost::make_shared<Glass>();
      break;
    case MATERIAL_TYPE_IRON:
      material = boost::make_shared<Iron>();
      break;
    case MATERIAL_TYPE_LEATHER:
      material = boost::make_shared<Leather>();
      break;
    case MATERIAL_TYPE_PAPER:
      material = boost::make_shared<Paper>();
      break;
    case MATERIAL_TYPE_STEEL:
      material = boost::make_shared<Steel>();
      break;
    case MATERIAL_TYPE_STONE:
      material = boost::make_shared<Stone>();
      break;
    case MATERIAL_TYPE_WOOD:
      material = boost::make_shared<Wood>();
      break;
    case MATERIAL_TYPE_MARBLE:
      material = boost::make_shared<Marble>();
      break;
    case MATERIAL_TYPE_ONYX:
      material = boost::make_shared<Onyx>();
      break;
    case MATERIAL_TYPE_IVORY:
      material = boost::make_shared<Ivory>();
      break;
    default:
      material = boost::make_shared<Wood>();
      break;
  }

  return material;
}

// JCD FIXME: Unit tests to ensure that the type of the
// created material matches the input type.
#ifdef UNIT_TESTS
#include "unit_tests/MaterialFactory_test.cpp"
#endif

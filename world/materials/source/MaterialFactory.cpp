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

MaterialSerializationMap MaterialFactory::material_map;

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

MaterialPtr MaterialFactory::create_material(const ClassIdentifier clid)
{
  MaterialPtr material;

  if (material_map.empty())
  {
    initialize_material_map();
  }

  MaterialSerializationMap::iterator m_it = material_map.find(clid);

  if (m_it != material_map.end())
  {
    material = MaterialPtr(m_it->second->clone());
  }

  return material;
}

void MaterialFactory::initialize_material_map()
{
  MaterialPtr cloth   = boost::make_shared<Cloth>();
  MaterialPtr dscale  = boost::make_shared<DragonScale>();
  MaterialPtr glass   = boost::make_shared<Glass>();
  MaterialPtr iron    = boost::make_shared<Iron>();
  MaterialPtr ivory   = boost::make_shared<Ivory>();
  MaterialPtr leather = boost::make_shared<Leather>();
  MaterialPtr marble  = boost::make_shared<Marble>();
  MaterialPtr onyx    = boost::make_shared<Onyx>();
  MaterialPtr paper   = boost::make_shared<Paper>();
  MaterialPtr steel   = boost::make_shared<Steel>();
  MaterialPtr stone   = boost::make_shared<Stone>();
  MaterialPtr wood    = boost::make_shared<Wood>();

  material_map.insert(make_pair(CLASS_ID_CLOTH, cloth));
  material_map.insert(make_pair(CLASS_ID_DRAGONSCALE, dscale));
  material_map.insert(make_pair(CLASS_ID_GLASS, glass));
  material_map.insert(make_pair(CLASS_ID_IRON, iron));
  material_map.insert(make_pair(CLASS_ID_IVORY, ivory));
  material_map.insert(make_pair(CLASS_ID_LEATHER, leather));
  material_map.insert(make_pair(CLASS_ID_MARBLE, marble));
  material_map.insert(make_pair(CLASS_ID_ONYX, onyx));
  material_map.insert(make_pair(CLASS_ID_PAPER, paper));
  material_map.insert(make_pair(CLASS_ID_STEEL, steel));
  material_map.insert(make_pair(CLASS_ID_STONE, wood));
  material_map.insert(make_pair(CLASS_ID_WOOD, wood));
}

// JCD FIXME: Unit tests to ensure that the type of the
// created material matches the input type.
#ifdef UNIT_TESTS
#include "unit_tests/MaterialFactory_test.cpp"
#endif

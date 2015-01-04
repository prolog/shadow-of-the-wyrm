#include "MaterialFactory.hpp"
#include "Bone.hpp"
#include "Cloth.hpp"
#include "DragonScale.hpp"
#include "Glass.hpp"
#include "Gold.hpp"
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
  static_assert(MaterialType::MATERIAL_TYPE_LAST == MaterialType(14), "Unexpected MATERIAL_TYPE_LAST");

  MaterialPtr material;

  switch(type)
  {
    case MaterialType::MATERIAL_TYPE_CLOTH:
      material = std::make_shared<Cloth>();
      break;
    case MaterialType::MATERIAL_TYPE_DRAGON_SCALE:
      material = std::make_shared<DragonScale>();
      break;
    case MaterialType::MATERIAL_TYPE_GLASS:
      material = std::make_shared<Glass>();
      break;
    case MaterialType::MATERIAL_TYPE_IRON:
      material = std::make_shared<Iron>();
      break;
    case MaterialType::MATERIAL_TYPE_LEATHER:
      material = std::make_shared<Leather>();
      break;
    case MaterialType::MATERIAL_TYPE_PAPER:
      material = std::make_shared<Paper>();
      break;
    case MaterialType::MATERIAL_TYPE_STEEL:
      material = std::make_shared<Steel>();
      break;
    case MaterialType::MATERIAL_TYPE_STONE:
      material = std::make_shared<Stone>();
      break;
    case MaterialType::MATERIAL_TYPE_WOOD:
      material = std::make_shared<Wood>();
      break;
    case MaterialType::MATERIAL_TYPE_MARBLE:
      material = std::make_shared<Marble>();
      break;
    case MaterialType::MATERIAL_TYPE_ONYX:
      material = std::make_shared<Onyx>();
      break;
    case MaterialType::MATERIAL_TYPE_IVORY:
      material = std::make_shared<Ivory>();
      break;
    case MaterialType::MATERIAL_TYPE_BONE:
      material = std::make_shared<Bone>();
      break;
    case MaterialType::MATERIAL_TYPE_GOLD:
      material = std::make_shared<Gold>();
      break;
    default:
      material = std::make_shared<Wood>();
      break;
  }

  return material;
}

#ifdef UNIT_TESTS
#include "unit_tests/MaterialFactory_test.cpp"
#endif

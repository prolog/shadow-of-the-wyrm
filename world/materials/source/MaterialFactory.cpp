#include "MaterialFactory.hpp"
#include "Bone.hpp"
#include "Clay.hpp"
#include "Cloth.hpp"
#include "DragonScale.hpp"
#include "Gases.hpp"
#include "Glass.hpp"
#include "Gold.hpp"
#include "Iron.hpp"
#include "Ivory.hpp"
#include "Leather.hpp"
#include "Marble.hpp"
#include "Meat.hpp"
#include "Onyx.hpp"
#include "Paper.hpp"
#include "PlantMaterial.hpp"
#include "Steel.hpp"
#include "Stone.hpp"
#include "UnknownMaterial.hpp"
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
  static_assert(MaterialType::MATERIAL_TYPE_LAST == MaterialType(19), "Unexpected MATERIAL_TYPE_LAST");

  MaterialPtr material;

  switch(type)
  {
    case MaterialType::MATERIAL_TYPE_CLOTH:
      material = std::make_unique<Cloth>();
      break;
    case MaterialType::MATERIAL_TYPE_DRAGON_SCALE:
      material = std::make_unique<DragonScale>();
      break;
    case MaterialType::MATERIAL_TYPE_GLASS:
      material = std::make_unique<Glass>();
      break;
    case MaterialType::MATERIAL_TYPE_IRON:
      material = std::make_unique<Iron>();
      break;
    case MaterialType::MATERIAL_TYPE_LEATHER:
      material = std::make_unique<Leather>();
      break;
    case MaterialType::MATERIAL_TYPE_PAPER:
      material = std::make_unique<Paper>();
      break;
    case MaterialType::MATERIAL_TYPE_STEEL:
      material = std::make_unique<Steel>();
      break;
    case MaterialType::MATERIAL_TYPE_STONE:
      material = std::make_unique<Stone>();
      break;
    case MaterialType::MATERIAL_TYPE_WOOD:
      material = std::make_unique<Wood>();
      break;
    case MaterialType::MATERIAL_TYPE_MARBLE:
      material = std::make_unique<Marble>();
      break;
    case MaterialType::MATERIAL_TYPE_ONYX:
      material = std::make_unique<Onyx>();
      break;
    case MaterialType::MATERIAL_TYPE_IVORY:
      material = std::make_unique<Ivory>();
      break;
    case MaterialType::MATERIAL_TYPE_BONE:
      material = std::make_unique<Bone>();
      break;
    case MaterialType::MATERIAL_TYPE_GOLD:
      material = std::make_unique<Gold>();
      break;
    case MaterialType::MATERIAL_TYPE_GASES:
      material = std::make_unique<Gases>();
      break;
    case MaterialType::MATERIAL_TYPE_MEAT:
      material = std::make_unique<Meat>();
      break;
    case MaterialType::MATERIAL_TYPE_CLAY:
      material = std::make_unique<Clay>();
      break;
    case MaterialType::MATERIAL_TYPE_PLANT:
      material = std::make_unique<PlantMaterial>();
      break;
    case MaterialType::MATERIAL_TYPE_UNKNOWN:
    default:
      material = std::make_unique<UnknownMaterial>();
      break;
  }

  return material;
}

#ifdef UNIT_TESTS
#include "unit_tests/MaterialFactory_test.cpp"
#endif

#include "MaterialTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

map<MaterialType, string> MaterialTextKeys::material_sids;

// Materials
MaterialTextKeys::MaterialTextKeys()
{
}

MaterialTextKeys::~MaterialTextKeys()
{
}

void MaterialTextKeys::init_material_sids()
{
  material_sids = {{MaterialType::MATERIAL_TYPE_CLOTH, MATERIAL_CLOTH},
                   {MaterialType::MATERIAL_TYPE_DRAGON_SCALE, MATERIAL_DRAGON_SCALE},
                   {MaterialType::MATERIAL_TYPE_GLASS, MATERIAL_GLASS},
                   {MaterialType::MATERIAL_TYPE_IRON, MATERIAL_IRON},
                   {MaterialType::MATERIAL_TYPE_LEATHER, MATERIAL_LEATHER},
                   {MaterialType::MATERIAL_TYPE_PAPER, MATERIAL_PAPER},
                   {MaterialType::MATERIAL_TYPE_STEEL, MATERIAL_STEEL},
                   {MaterialType::MATERIAL_TYPE_STONE, MATERIAL_STONE},
                   {MaterialType::MATERIAL_TYPE_WOOD, MATERIAL_WOOD},
                   {MaterialType::MATERIAL_TYPE_MARBLE, MATERIAL_MARBLE},
                   {MaterialType::MATERIAL_TYPE_ONYX, MATERIAL_ONYX},
                   {MaterialType::MATERIAL_TYPE_IVORY, MATERIAL_IVORY},
                   {MaterialType::MATERIAL_TYPE_BONE, MATERIAL_BONE},
                   {MaterialType::MATERIAL_TYPE_GOLD, MATERIAL_GOLD}};
}

const string MaterialTextKeys::get_material(const MaterialType mt)
{
  static_assert(MaterialType::MATERIAL_TYPE_LAST == MaterialType(14), "Unexpected MATERIAL_TYPE_LAST!");

  if (material_sids.empty())
  {
    init_material_sids();
  }

  string material = "?";

  auto m_it = material_sids.find(mt);

  if (m_it != material_sids.end())
  {
    material = m_it->second;
  }

  return StringTable::get(material);
}

const string MaterialTextKeys::MATERIAL_CLOTH        = "MATERIAL_CLOTH";
const string MaterialTextKeys::MATERIAL_DRAGON_SCALE = "MATERIAL_DRAGON_SCALE";
const string MaterialTextKeys::MATERIAL_GLASS        = "MATERIAL_GLASS";
const string MaterialTextKeys::MATERIAL_GOLD         = "MATERIAL_GOLD";
const string MaterialTextKeys::MATERIAL_IRON         = "MATERIAL_IRON";
const string MaterialTextKeys::MATERIAL_LEATHER      = "MATERIAL_LEATHER";
const string MaterialTextKeys::MATERIAL_PAPER        = "MATERIAL_PAPER";
const string MaterialTextKeys::MATERIAL_STEEL        = "MATERIAL_STEEL";
const string MaterialTextKeys::MATERIAL_STONE        = "MATERIAL_STONE";
const string MaterialTextKeys::MATERIAL_WOOD         = "MATERIAL_WOOD";
const string MaterialTextKeys::MATERIAL_MARBLE       = "MATERIAL_MARBLE";
const string MaterialTextKeys::MATERIAL_ONYX         = "MATERIAL_ONYX";
const string MaterialTextKeys::MATERIAL_IVORY        = "MATERIAL_IVORY";
const string MaterialTextKeys::MATERIAL_BONE         = "MATERIAL_BONE";
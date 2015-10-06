#pragma once
#include <map>
#include <string>
#include "MaterialTypes.hpp"

class MaterialTextKeys
{
  public:
    static const std::string get_material(const MaterialType mt);

    static const std::string MATERIAL_CLOTH;
    static const std::string MATERIAL_DRAGON_SCALE;
    static const std::string MATERIAL_GLASS;
    static const std::string MATERIAL_GOLD;
    static const std::string MATERIAL_IRON;
    static const std::string MATERIAL_LEATHER;
    static const std::string MATERIAL_PAPER;
    static const std::string MATERIAL_STEEL;
    static const std::string MATERIAL_STONE;
    static const std::string MATERIAL_WOOD;
    static const std::string MATERIAL_MARBLE;
    static const std::string MATERIAL_ONYX;
    static const std::string MATERIAL_IVORY;
    static const std::string MATERIAL_BONE;
    
  protected:
    MaterialTextKeys();
    ~MaterialTextKeys();

    static void init_material_sids();

    static std::map<MaterialType, std::string> material_sids;
};

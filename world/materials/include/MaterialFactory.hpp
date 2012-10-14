#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Material.hpp"

typedef std::map<ClassIdentifier, MaterialPtr> MaterialSerializationMap;

class MaterialFactory
{
  public:
    static MaterialPtr create_material(const MaterialType type);
    static MaterialPtr create_material(const ClassIdentifier clid);

  protected:
    MaterialFactory();
    ~MaterialFactory();

    static void initialize_material_map();

    static MaterialSerializationMap material_map;
};

#pragma once
#include "Material.hpp"

class MaterialFactory
{
  public:
    static MaterialPtr create_material(const MaterialType type);

  protected:
    MaterialFactory();
    ~MaterialFactory();
};

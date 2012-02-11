#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include "MaterialTypes.hpp"

enum MaterialType;

class Material
{
  public:
    // The type of the material
    virtual MaterialType get_type() const = 0;
    
    // The name of the material
    virtual std::string get_name_sid() const = 0;

    // The material's properties when exposed to the appropriate
    // damage type.
    virtual bool get_is_flammable() const = 0;
    virtual bool get_is_explosive() const = 0;
    virtual bool get_is_corrodible() const = 0;
    virtual bool get_can_rust() const = 0;
};

typedef boost::shared_ptr<Material> MaterialPtr;

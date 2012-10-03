#pragma once
#include "Material.hpp"

class Paper : public Material
{
  public:
    MaterialType get_type() const;
    std::string get_name_sid() const;

    bool get_is_flammable() const;
    bool get_is_explosive() const;
    bool get_is_corrodible() const;
    bool get_can_rust() const;
    
    virtual Colour get_colour() const;
    
    Material* clone();
};

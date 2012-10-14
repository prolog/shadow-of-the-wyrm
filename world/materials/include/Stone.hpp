#pragma once
#include "Material.hpp"

class Stone : public Material
{
  public:
    MaterialType get_type() const;
    std::string get_name_sid() const;

    bool get_is_flammable() const;
    bool get_is_explosive() const;
    bool get_is_corrodible() const;
    bool get_can_rust() const;
    
    Material* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

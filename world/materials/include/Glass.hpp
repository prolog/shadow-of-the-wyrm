#pragma once
#include "Material.hpp"

class Glass : public Material
{
  public:
    MaterialType get_type() const override;
    std::string get_name_sid() const override;

    bool get_is_flammable() const override;
    bool get_is_explosive() const override;
    bool get_is_corrodible() const override;
    bool get_crumbles() const override;
    
    Material* clone() override;
};

#pragma once
#include "Material.hpp"

class Gold : public Material
{
  public:
    MaterialType get_type() const override;
    std::string  get_name_sid() const override;

    bool get_is_flammable() const override;
    bool get_is_explosive() const override;
    bool get_is_corrodible() const override;
    bool get_can_rust() const override;
    
    virtual Colour get_colour() const override;

    Material* clone() override;
};


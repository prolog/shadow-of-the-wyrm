#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

class Bed : public Feature
{
  public:
    Bed(const Symbol& new_symbol);
    virtual Feature* clone() override;

    bool operator==(const Bed& t) const;

    virtual float get_hp_regeneration_multiplier() const override;
    virtual float get_ap_regeneration_multiplier() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};


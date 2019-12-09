#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

// This is a "north-south" pew: the symbol is '-'.
// "east-west" pews are defined in EastWestPew.hpp.
class Pew : public Feature
{
  public:
    Pew(const Symbol& new_symbol);
    virtual Feature* clone() override;

    virtual float get_piety_loss_multiplier() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

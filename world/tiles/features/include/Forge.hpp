#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

class Forge : public Feature
{
  public:
    Forge(const Symbol& new_symbol);
    virtual Feature* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

// Benches are made of iron, and increase healing rates while sitting by
// a little.
class Bench : public Feature
{
  public:
    Bench(const Symbol& new_symbol);
    virtual Feature* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

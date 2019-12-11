#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

class FirePillar : public Feature
{
  public:
    FirePillar(const Symbol& new_symbol);
    virtual Feature* clone() override;

    virtual bool get_is_blocking() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

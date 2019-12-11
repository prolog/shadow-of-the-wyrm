#pragma once
#include "Feature.hpp"

class Tannery : public Feature
{
  public:
    Tannery(const Symbol& new_symbol);
    virtual Feature* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

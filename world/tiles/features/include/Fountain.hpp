#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

class Fountain : public Feature
{
  public:
    Fountain(const Symbol& new_symbol);
    virtual Feature* clone() override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

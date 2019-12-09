#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

class Forge : public Feature
{
  public:
    Forge(const Symbol& new_symbol);
    virtual Feature* clone() override;

    bool operator==(const Forge& b) const;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

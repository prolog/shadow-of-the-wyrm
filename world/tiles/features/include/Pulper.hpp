#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

class Pulper : public Feature
{
  public:
    Pulper(const Symbol& new_symbol);
    virtual Feature* clone() override;

    bool operator==(const Pulper& p) const;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

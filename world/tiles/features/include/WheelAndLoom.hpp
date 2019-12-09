#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

class WheelAndLoom : public Feature
{
  public:
    WheelAndLoom(const Symbol& new_symbol);
    virtual Feature* clone() override;

    bool operator==(const WheelAndLoom& j) const;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};


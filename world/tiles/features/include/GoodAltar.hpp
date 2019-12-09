#pragma once
#include "Altar.hpp"

// GoodAltar is a convenience class that sets up an altar for a 
// particular good-aligned deity.
class GoodAltar : public Altar
{
  public:
    GoodAltar(const Symbol& new_symbol);
    GoodAltar(const Symbol& new_symbol, const std::string& new_deity_id);
    virtual Feature* clone() override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

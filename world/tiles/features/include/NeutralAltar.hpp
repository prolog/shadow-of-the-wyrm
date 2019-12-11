#pragma once
#include "Altar.hpp"

// NeutralAltar is a convenience class that sets up an altar
// appropriately for a neutral deity.
class NeutralAltar : public Altar
{
  public:
    NeutralAltar(const Symbol& new_symbol);
    NeutralAltar(const Symbol& new_symbol, const std::string& new_deity_id);
    virtual Feature* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

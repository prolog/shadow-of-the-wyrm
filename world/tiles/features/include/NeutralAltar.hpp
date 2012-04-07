#pragma once
#include "Altar.hpp"

// NeutralAltar is a convenience class that sets up an altar
// appropriately for a neutral deity.
class NeutralAltar : public Altar
{
  public:
    NeutralAltar(const std::string& new_deity_id);
    
    virtual std::string get_description_sid() const;
};

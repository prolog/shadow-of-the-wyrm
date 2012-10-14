#pragma once
#include "Altar.hpp"

// GoodAltar is a convenience class that sets up an altar for a 
// particular good-aligned deity.
class GoodAltar : public Altar
{
  public:
    GoodAltar();
    GoodAltar(const std::string& new_deity_id);
    
    virtual std::string get_description_sid() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

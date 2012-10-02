#pragma once
#include "Altar.hpp"

// A convenience class that sets up an evil altar appropriately.
class EvilAltar : public Altar
{
  public:
    EvilAltar();
    EvilAltar(const std::string& new_deity_id);
    
    std::string get_description_sid() const;
};

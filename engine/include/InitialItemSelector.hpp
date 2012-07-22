#pragma once
#include "InitialItem.hpp"

class InitialItemSelector
{
  public:
    std::string get_item_id(const std::string& race_id, const InitialItem& initial_item) const;
    
  protected:
    std::string get_random_item_id(const InitialItem& initial_item) const;
    std::string get_racial_item_id(const std::string& race_id, const InitialItem& initial_item) const;
};

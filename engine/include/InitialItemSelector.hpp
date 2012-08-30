#pragma once
#include "InitialItem.hpp"

class InitialItemSelector
{
  public:
    std::pair<std::string, uint> get_item_details(const std::string& race_id, const InitialItem& initial_item) const;
    
  protected:
    std::pair<std::string, uint> get_random_item_details(const InitialItem& initial_item) const;
    std::pair<std::string, uint> get_racial_item_details(const std::string& race_id, const InitialItem& initial_item) const;
};

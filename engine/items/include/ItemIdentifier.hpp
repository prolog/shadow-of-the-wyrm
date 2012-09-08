#pragma once
#include <string>
#include "Item.hpp"

// A class for working with logic based around an item's "identified" status.
class ItemIdentifier
{
  public:
    // Functions for querying or modifying a particular item's
    // identification status.
    void set_item_identified(const std::string& base_item_id, const bool is_identified) const;
    bool get_item_identified(const std::string& base_item_id) const;

    // Get the appropriate description (identified or unidentified) for
    // the items whose base item identified is base_item_id.
    std::string get_appropriate_description_sid(const std::string& base_item_id) const;
    std::string get_appropriate_usage_description_sid(const std::string& base_item_id) const;
    
  protected:
    ItemPtr get_base_item(const std::string& base_item_id) const;
};

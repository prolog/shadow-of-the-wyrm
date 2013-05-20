#pragma once
#include <map>
#include <string>
#include "ItemTypes.hpp"

class ItemStatusTextKeys
{
  public:
    ItemStatusTextKeys();
    std::string get_item_status_and_description(const ItemStatus item_status, const std::string& item_desc);

    static const std::string STATUS_BLESSED;
    static const std::string STATUS_UNCURSED;
    static const std::string STATUS_CURSED;

  protected:
    static const std::string ITEM_STATUS_AND_DESCRIPTION;

    void initialize_item_status_string_map();

    std::map<ItemStatus, std::string> item_status_string_map;
};

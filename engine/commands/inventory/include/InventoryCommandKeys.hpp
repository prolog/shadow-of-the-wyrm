#pragma once
#include <string>

class InventoryCommandKeys
{
  public:
    static const std::string EXIT_INVENTORY;
    static const std::string CLEAR_FILTER;
    static const std::string FILTER_VIEW;
    static const std::string SELECT_ITEM;
    
  protected:
    InventoryCommandKeys();
    ~InventoryCommandKeys();
};

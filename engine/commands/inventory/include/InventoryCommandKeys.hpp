#pragma once
#include <string>

class InventoryCommandKeys
{
  public:
    static std::string EXIT_INVENTORY;
    static std::string CLEAR_FILTER;
    static std::string FILTER_VIEW;
    static std::string NEXT_PAGE;
    static std::string PREVIOUS_PAGE;
    static std::string SELECT_ITEM;
    
  protected:
    InventoryCommandKeys();
    ~InventoryCommandKeys();
};

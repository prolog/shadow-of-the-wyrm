#pragma once
#include <string>
#include <memory>
#include "Colours.hpp"
#include "ItemTypes.hpp"

// Information about an ItemType for the display
class DisplayItemType
{
  public:
    DisplayItemType(const std::string& new_symbol, const Colour new_colour, const ItemType new_item_type, const std::string& new_description);
    ~DisplayItemType();
    
    void set_symbol(const std::string& new_symbol);
    std::string get_symbol() const;
    
    void set_colour(const Colour new_colour);
    Colour get_colour() const;

    void set_item_type(const ItemType new_item_type);
    ItemType get_item_type() const;
    
    void set_description(const std::string& new_description);
    std::string get_description() const;
    
    bool operator<(const DisplayItemType& compare) const;
    
  protected:
    std::string symbol;
    Colour colour;
    ItemType item_type;
    std::string description;
};

using DisplayItemTypePtr = std::shared_ptr<DisplayItemType>;

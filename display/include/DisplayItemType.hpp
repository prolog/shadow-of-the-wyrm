#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include "Colours.hpp"

// Information about an ItemType for the display
class DisplayItemType
{
  public:
    DisplayItemType(const std::string& new_symbol, const Colour new_colour, const std::string& new_description);
    ~DisplayItemType();
    
    void set_symbol(const std::string& new_symbol);
    std::string get_symbol() const;
    
    void set_colour(const Colour new_colour);
    Colour get_colour() const;
    
    void set_description(const std::string& new_description);
    std::string get_description() const;
    
    bool operator<(const DisplayItemType& compare) const;
    
  protected:
    std::string symbol;
    Colour colour;
    std::string description;
};

typedef boost::shared_ptr<DisplayItemType> DisplayItemTypePtr;

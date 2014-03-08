#include "DisplayItemType.hpp"

using std::string;

DisplayItemType::DisplayItemType(const string& new_symbol, const Colour new_colour, const ItemType new_item_type, const string& new_description)
: symbol(new_symbol), colour(new_colour), item_type(new_item_type), description(new_description)
{
}

DisplayItemType::~DisplayItemType()
{
}

void DisplayItemType::set_symbol(const string& new_symbol)
{
  symbol = new_symbol;
}

string DisplayItemType::get_symbol() const
{
  return symbol;
}

void DisplayItemType::set_colour(const Colour new_colour)
{
  colour = new_colour;
}

Colour DisplayItemType::get_colour() const
{
  return colour;
}

void DisplayItemType::set_item_type(const ItemType new_item_type)
{
  item_type = new_item_type;
}

ItemType DisplayItemType::get_item_type() const
{
  return item_type;
}

void DisplayItemType::set_description(const string& new_description)
{
  description = new_description;
}

string DisplayItemType::get_description() const
{
  return description;
}

bool DisplayItemType::operator<(const DisplayItemType& compare) const
{
  if (get_description() < compare.get_description())
  {
    return true;
  }
  
  return false;
}

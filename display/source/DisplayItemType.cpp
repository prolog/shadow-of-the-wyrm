#include "DisplayItemType.hpp"

using std::string;

DisplayItemType::DisplayItemType(const string& new_symbol, const Colour new_colour, const string& new_description)
: symbol(new_symbol), colour(new_colour), description(new_description)
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

void DisplayItemType::set_description(const string& new_description)
{
  description = new_description;
}

string DisplayItemType::get_description() const
{
  return description;
}


#include "DisplayItem.hpp"

using namespace std;

DisplayItem::DisplayItem()
: colour(COLOUR_WHITE)
{
}

DisplayItem::~DisplayItem()
{
}

void DisplayItem::set_description(const string& new_description)
{
  description = new_description;
}

string DisplayItem::get_description() const
{
  return description;
}

void DisplayItem::set_flags(const DisplayItemFlagsVec& new_flags)
{
  flags = new_flags;
}

DisplayItemFlagsVec DisplayItem::get_flags() const
{
  return flags;
}

void DisplayItem::set_colour(const Colour new_colour)
{
  colour = new_colour;
}

Colour DisplayItem::get_colour() const
{
  return colour;
}

void DisplayItem::set_id(const string& new_id)
{
  id = new_id;
}

string DisplayItem::get_id() const
{
  return id;
}

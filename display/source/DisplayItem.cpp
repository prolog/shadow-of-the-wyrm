#include "DisplayItem.hpp"

using namespace std;

DisplayItem::DisplayItem()
{
}

DisplayItem::~DisplayItem()
{
}

void DisplayItem::set_description(const string& new_description)
{
  description = new_description;
}

string DisplayItem::get_description()
{
  return description;
}

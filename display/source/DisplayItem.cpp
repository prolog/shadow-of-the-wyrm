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

string DisplayItem::get_description() const
{
  return description;
}

void DisplayItem::set_id(const string& new_id)
{
  id = new_id;
}

string DisplayItem::get_id() const
{
  return id;
}

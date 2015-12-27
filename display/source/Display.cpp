#include "Display.hpp"
#include "Serialize.hpp"

using namespace std;

bool Display::serialize(ostream& stream) const
{
  Serialize::write_string_map(stream, display_properties);

  return true;
}

bool Display::deserialize(istream& stream)
{
  Serialize::read_string_map(stream, display_properties);

  return true;
}

void Display::set_properties(const map<string, string>& new_properties)
{
  display_properties = new_properties;
}

void Display::set_property(const string& property, const string& value)
{
  display_properties[property] = value;
}

bool Display::remove_property(const string& property)
{
  bool removed = false;
  auto p_it = display_properties.find(property);

  if (p_it != display_properties.end())
  {
    display_properties.erase(p_it);
    removed = true;
  }

  return removed;
}

string Display::get_property(const string& property) const
{
  string value;

  auto prop_it = display_properties.find(property);

  if (prop_it != display_properties.end())
  {
    value = prop_it->second;
  }

  return value;
}


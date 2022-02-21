#include "DangerLevelCalculator.hpp"

using namespace std;

void DangerLevelCalculator::set_property(const string& property_name, const string& property_value)
{
  properties[property_name] = property_value;
}

string DangerLevelCalculator::get_property(const string& property_name) const
{
  string value;
  auto p_it = properties.find(property_name);

  if (p_it != properties.end())
  {
    value = p_it->second;
  }

  return value;
}

void DangerLevelCalculator::set_properties(const map<string, string>& new_properties)
{
  properties = new_properties;
}

map<string, string> DangerLevelCalculator::get_properties() const
{
  return properties;
}

#ifdef UNIT_TESTS
#include "unit_tests/DangerLevelCalculator_test.cpp"
#endif
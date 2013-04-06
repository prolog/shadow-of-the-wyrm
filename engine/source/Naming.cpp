#include <algorithm>
#include "Naming.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

uint Naming::MAXIMUM_NAME_SIZE = 15;

Naming::Naming()
{
}

string Naming::clean_name(const string& name)
{
  string new_name = name;

  if (new_name.empty())
  {
    new_name = StringTable::get(TextKeys::DEFAULT_PLAYER_NAME);
  }

  if (new_name.size() > 0)
  {
    size_t new_name_length = min(new_name.size(), MAXIMUM_NAME_SIZE);
    new_name = new_name.substr(0, new_name_length);
  }

  return new_name;
}

uint Naming::get_max_name_size()
{
  return MAXIMUM_NAME_SIZE;
}

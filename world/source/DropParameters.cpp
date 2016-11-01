#include "DropParameters.hpp"

using namespace std;

DropParameters::DropParameters()
: percent_chance(0), min(1), max(1)
{
}

DropParameters::DropParameters(const string& new_item_base_id, const int new_percent_chance, const int new_min, const int new_max)
: item_base_id(new_item_base_id), percent_chance(new_percent_chance), min(new_min), max(new_max)
{
}

string DropParameters::get_item_base_id() const
{
  return item_base_id;
}

int DropParameters::get_percent_chance() const
{
  return percent_chance;
}

int DropParameters::get_min() const
{
  return min;
}

int DropParameters::get_max() const
{
  return max;
}

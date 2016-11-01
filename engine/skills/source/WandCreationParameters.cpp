#include "WandCreationParameters.hpp"

using namespace std;

WandCreationParameters::WandCreationParameters(const string& new_spell_id, const int new_num_charges, const int new_castings_per_charge)
: spell_id(new_spell_id), num_charges(new_num_charges), castings_per_charge(new_castings_per_charge)
{
}

string WandCreationParameters::get_spell_id() const
{
  return spell_id;
}

int WandCreationParameters::get_num_charges() const
{
  return num_charges;
}

int WandCreationParameters::get_castings_per_charge() const
{
  return castings_per_charge;
}


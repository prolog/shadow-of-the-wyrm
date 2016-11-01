#pragma once
#include <string>

class WandCreationParameters
{
  public:
    WandCreationParameters(const std::string& new_spell_id, const int new_num_charges, const int new_castings_per_charge);

    std::string get_spell_id() const;
    int get_num_charges() const;
    int get_castings_per_charge() const;

  protected:
    std::string spell_id;
    int num_charges;
    int castings_per_charge;
};


#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"

class MembershipsDumper : public StringConverter
{
  public:
    MembershipsDumper(CreaturePtr new_creature, const uint new_max_cols);
  
    std::string str() const override;

  protected:
    std::string get_memberships() const;

    CreaturePtr creature;
    uint num_cols;
};

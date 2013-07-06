#pragma once
#include "IDamageEffect.hpp"

// Does nothing, which is the default behaviour for a damage type until
// otherwise specified.
class DefaultDamageEffect : public IDamageEffect
{
  public:
    void apply(CreaturePtr creature, const int damage_dealt) const;
    std::string get_player_application_message() const;
};


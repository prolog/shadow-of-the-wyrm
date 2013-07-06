#pragma once
#include "Creature.hpp"

// IDamageEffect defines an interface for applying damage effects (such as 
// poison, blindness, etc).
class IDamageEffect
{
  public:
    virtual ~IDamageEffect() {};

    // apply(...) decides whether to apply the damage effect, based on
    // certain factors (e.g., a base chance), as well as by the affected
    // creature and the amount of damage dealt.
    virtual void apply(CreaturePtr creature, const int damage_dealt) const = 0;

    // The message that gets added via the message manager when the affected
    // creature is the player.
    virtual std::string get_player_application_message() const = 0;
};

typedef boost::shared_ptr<IDamageEffect> IDamageEffectPtr;


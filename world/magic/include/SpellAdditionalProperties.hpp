#pragma once
#include <string>

// All the additional properties used by spells for specifying
// spell-specific properties that not all spells require.
class SpellAdditionalProperties
{
  public:
    static const std::string PROPERTY_STATISTIC_MODIFIER_STR;
    static const std::string PROPERTY_STATISTIC_MODIFIER_DEX;
    static const std::string PROPERTY_STATISTIC_MODIFIER_AGI;
    static const std::string PROPERTY_STATISTIC_MODIFIER_HEA;
    static const std::string PROPERTY_STATISTIC_MODIFIER_INT;
    static const std::string PROPERTY_STATISTIC_MODIFIER_WIL;
    static const std::string PROPERTY_STATISTIC_MODIFIER_CHA;
    static const std::string PROPERTY_STATISTIC_MODIFIER_EVADE;
    static const std::string PROPERTY_STATISTIC_MODIFIER_SOAK;

    // Note that status effects are intentionally not included here.
    // Even though in the game status effects are modelled as a Modifier
    // that has a list of status effects, it isn't intended that spells
    // set status effects directly - rather, they should set status effects
    // by doing the appropriate type of damage, or by doing damage with a
    // certain list of effects.

    static const std::string PROPERTY_STATISTIC_MODIFIER_WEAR_OFF_SID;

  protected:
    SpellAdditionalProperties();
    ~SpellAdditionalProperties();
};


#pragma once
#include <string>

class CreatureProperties
{
  public:
    static const std::string CREATURE_PROPERTIES_CHAT_SCRIPT;
    static const std::string CREATURE_PROPERTIES_LAST_BESTIARY_SEARCH;
    static const std::string CREATURE_PROPERTIES_HASTE_MODIFIER; // used for both haste & slow
    static const std::string CREATURE_PROPERTIES_DISFIG_STR_MOD;
    static const std::string CREATURE_PROPERTIES_DISFIG_DEX_MOD;
    static const std::string CREATURE_PROPERTIES_DISFIG_AGI_MOD;
    static const std::string CREATURE_PROPERTIES_DISFIG_HEA_MOD;
    static const std::string CREATURE_PROPERTIES_DISFIG_INT_MOD;
    static const std::string CREATURE_PROPERTIES_DISFIG_WIL_MOD;
    static const std::string CREATURE_PROPERTIES_DISFIG_CHA_MOD;
    static const std::string CREATURE_PROPERTIES_FOLLOWS_CR_ID; // used for summoned/bound creatures

  protected:
    CreatureProperties();
    ~CreatureProperties();
};

#pragma once
#include <string>

class CreatureProperties
{
  public:
    static const std::string CREATURE_PROPERTIES_SPEECH_TEXT_SID;
    static const std::string CREATURE_PROPERTIES_LAST_BESTIARY_SEARCH;
    static const std::string CREATURE_PROPERTIES_HASTE_MODIFIER; // used for both haste & slow
    static const std::string CREATURE_PROPERTIES_FOLLOWS_CR_ID; // used for summoned/bound creatures
    static const std::string CREATURE_PROPERTIES_AUTOMOVEMENT_COORDS_VISITED;
    static const std::string CREATURE_PROPERTIES_LEAVES_CORPSE;
    static const std::string CREATURE_PROPERTIES_LEAVES_EQUIPMENT;
    static const std::string CREATURE_PROPERTIES_ALLOWS_RANDOM_DROPS;
    static const std::string CREATURE_PROPERTIES_STOLEN_FROM;
    static const std::string CREATURE_PROPERTIES_PACIFIED;
    static const std::string CREATURE_PROPERTIES_WINNER;
    static const std::string CREATURE_PROPERTIES_IGNORE_RACIAL_MOVEMENT_RESTRICTIONS;

  protected:
    CreatureProperties();
    ~CreatureProperties();
};

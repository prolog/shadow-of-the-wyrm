#pragma once
#include <string>

enum struct BurdenLevel
{
  BURDEN_LEVEL_UNBURDENED,
  BURDEN_LEVEL_BURDENED,
  BURDEN_LEVEL_STRAINED,
  BURDEN_LEVEL_OVERBURDENED
};

enum struct HungerLevel
{
  HUNGER_LEVEL_STUFFED,
  HUNGER_LEVEL_FULL,
  HUNGER_LEVEL_NORMAL,
  HUNGER_LEVEL_HUNGRY,
  HUNGER_LEVEL_STARVING,
  HUNGER_LEVEL_DYING
};

class StatusIdentifiers
{
  public:
    static const std::string STATUS_ID_POISON;
    static const std::string STATUS_ID_MUTE;
    static const std::string STATUS_ID_PARALYSIS;
    static const std::string STATUS_ID_SLOWNESS;
    static const std::string STATUS_ID_HASTE;
    static const std::string STATUS_ID_STONE;
    static const std::string STATUS_ID_BLOODIED;
    static const std::string STATUS_ID_STUNNED;
    static const std::string STATUS_ID_EXPOSED;
    static const std::string STATUS_ID_DISFIGURED;
    static const std::string STATUS_ID_SPELLBOUND;
    static const std::string STATUS_ID_BLINDED;
    static const std::string STATUS_ID_INCORPOREAL;
    static const std::string STATUS_ID_DRUNK;
    static const std::string STATUS_ID_FLYING;
    static const std::string STATUS_ID_TIMEWALK;
    static const std::string STATUS_ID_SATED;
    static const std::string STATUS_ID_WATER_BREATHING;
    static const std::string STATUS_ID_RAGE;
    static const std::string STATUS_ID_HIDE;

  protected:
    StatusIdentifiers();
    ~StatusIdentifiers();
};

#pragma once
#include <string>

enum HungerLevel
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

  protected:
    StatusIdentifiers();
    ~StatusIdentifiers();
};

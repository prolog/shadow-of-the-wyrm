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

  protected:
    StatusIdentifiers();
    ~StatusIdentifiers();
};

#pragma once
#include <string>

class ConsumableConstants
{
  public:
    static const std::string CORPSE_DESCRIPTION_SID;
  	static const std::string CORPSE_SHORT_DESCRIPTION_SID;
    static const std::string CORPSE_RACE_ID;
    static const std::string CORPSE_CREATURE_ID;
    static const std::string CORPSE_SKINNED;

    static const int FOOD_POISON_APPLICATION_BONUS;
    static const int ALCOHOL_POISON_APPLICATION_BONUS;

  protected:
    ConsumableConstants();
    ~ConsumableConstants();
};


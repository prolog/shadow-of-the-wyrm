#pragma once
#include "Creature.hpp"
#include "Date.hpp"
#include "MapTypes.hpp"

class LineOfSightCalculator
{
  public:
    LineOfSightCalculator();
    int calculate_los_length(CreaturePtr creature, const MapType map_type, const TimeOfDayType tod);

    static const int DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH;

  protected:
    void initialize_base_tod_penalty();
    int calculate_night_vision_bonus(CreaturePtr creature, const TimeOfDayType tod);

    static std::map<TimeOfDayType, int> base_tod_penalty;
};
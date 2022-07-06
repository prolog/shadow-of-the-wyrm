#include "LineOfSightCalculator.hpp"

using namespace std;

const int LineOfSightCalculator::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH = 6;
map<TimeOfDayType, int> LineOfSightCalculator::base_tod_penalty;

LineOfSightCalculator::LineOfSightCalculator()
{
  if (base_tod_penalty.empty())
  {
    initialize_base_tod_penalty();
  }
}

int LineOfSightCalculator::calculate_los_length(CreaturePtr creature, const MapType map_type, const TimeOfDayType tod)
{
  int los_len = DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH;

  // Only the overworld is affected by TOD values
  if (creature != nullptr && (map_type == MapType::MAP_TYPE_OVERWORLD || map_type == MapType::MAP_TYPE_AIR))
  {
    auto btp_it = base_tod_penalty.find(tod);

    if (btp_it != base_tod_penalty.end())
    {
      int night_vision_bonus = calculate_night_vision_bonus(creature, tod);

      los_len -= btp_it->second;
      los_len += night_vision_bonus;
    }
  }

  los_len = std::max<int>(1, los_len);
  return los_len;
}

int LineOfSightCalculator::calculate_night_vision_bonus(CreaturePtr creature, const TimeOfDayType tod)
{
  int bonus = 0;

  if (creature != nullptr)
  {
    int skill_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_NIGHT_SIGHT);

    if (tod == TimeOfDayType::TIME_OF_DAY_DAWN || tod == TimeOfDayType::TIME_OF_DAY_DUSK)
    {
      if (skill_val >= 25)
      {
        bonus = 1;
      }
    }
    else if (tod == TimeOfDayType::TIME_OF_DAY_NIGHT)
    {
      // +1 to LOS for every 33 points
      bonus = skill_val / 33;
    }
  }

  return bonus;
}

void LineOfSightCalculator::initialize_base_tod_penalty()
{
  base_tod_penalty = {{TimeOfDayType::TIME_OF_DAY_UNDEFINED, 0},
                      {TimeOfDayType::TIME_OF_DAY_DAY, 0},
                      {TimeOfDayType::TIME_OF_DAY_DAWN, 1},
                      {TimeOfDayType::TIME_OF_DAY_DUSK, 1},
                      {TimeOfDayType::TIME_OF_DAY_NIGHT, 3}};
}

#ifdef UNIT_TESTS
#include "unit_tests/LineOfSightCalculator_test.cpp"
#endif

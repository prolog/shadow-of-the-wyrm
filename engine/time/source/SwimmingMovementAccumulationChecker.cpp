#include "CombatManager.hpp"
#include "StringConstants.hpp"
#include "SwimmingCalculator.hpp"
#include "SwimmingMovementAccumulationChecker.hpp"

// Check for damage due to swimming past the point of exhaustion.
void SwimmingMovementAccumulationChecker::check(CreaturePtr creature)
{
  if (creature)
  {
    SwimmingCalculator sc;
    
    int max_swimming_time = sc.calculate_maximum_swimming_time(sm.get_skill_value(creature, SKILL_GENERAL_SWIMMING));
    MovementAccumulation& movement_accumulation = creature->get_movement_accumulation_ref();
    int time_in_water = movement_accumulation.get_minutes_on_super_type_given_movement();

    if (time_in_water > max_swimming_time)
    {
      swim.drown(creature);
    }
    else
    {
      sm.check_skill(creature, SKILL_GENERAL_SWIMMING);
    }
  }
}

#include "CombatManager.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "SwimmingCalculator.hpp"
#include "SwimmingMovementAccumulationChecker.hpp"
#include "RNG.hpp"

// Check for damage due to swimming past the point of exhaustion.
void SwimmingMovementAccumulationChecker::check(CreaturePtr creature)
{
  if (creature)
  {
    SwimmingCalculator sc;
    MapPtr current_map = Game::instance().get_current_map();
    bool submerged = false;

    if (current_map != nullptr)
    {
      TilePtr tile = MapUtils::get_tile_for_creature(current_map, creature);
      submerged = tile && tile->get_submerged();
    }

    ulonglong max_swimming_time = static_cast<ulonglong>(sc.calculate_maximum_swimming_time(submerged, creature, creature->get_breathes()));
    MovementAccumulation& movement_accumulation = creature->get_movement_accumulation_ref();
    ulonglong time_in_water = movement_accumulation.get_minutes_on_super_type_given_movement();

    // If a creature has water breathing, it can basically swim forever.
    if ((time_in_water > max_swimming_time) && !creature->can_breathe(BreatheType::BREATHE_TYPE_WATER))
    {
      swim.process(creature, nullptr);
    }
    else
    {
      if (RNG::percent_chance(10))
      {
        sm.check_skill(creature, SkillType::SKILL_GENERAL_SWIMMING);
      }
    }
  }
}

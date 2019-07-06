#include "HidingCalculator.hpp"
#include "CoordUtils.hpp"
#include "MapUtils.hpp"

using namespace std;

const int HidingCalculator::HIDING_DIVISOR_AFTER_ATTACKING = 2;
const int HidingCalculator::MAX_DISTANCE_FOR_PENALTY = 10;
const int HidingCalculator::MAX_PCT_CHANCE_HIDE_CREATURES_PRESENT = 80;

int HidingCalculator::calculate_pct_chance_hide(CreaturePtr creature, MapPtr map, const TimeOfDayType tod) const
{
  int pct_chance_hide = 0;

  if (creature != nullptr && map != nullptr)
  {
    string creature_id = creature->get_id();

    // Get the creatures that can see the creature trying to hide.
    vector<string> creature_ids = MapUtils::get_creatures_with_creature_in_view(map, creature_id);

    if (creature_ids.empty())
    {
      pct_chance_hide = 100;
    }
    else
    {
      // Slightly easier to hide at dawn/dusk, much easier at night
      // TODO: Should not apply to underground, etc.
      int tod_modifier = get_tod_hide_modifier_for_map_type(tod, map->get_map_type());

      pct_chance_hide += creature->get_skills().get_value(SkillType::SKILL_GENERAL_HIDING);
      pct_chance_hide += tod_modifier;
      pct_chance_hide += get_viewing_creatures_modifier(creature, map, creature_ids);

      pct_chance_hide = std::min<int>(pct_chance_hide, MAX_PCT_CHANCE_HIDE_CREATURES_PRESENT);
    }

    // Ensure the value is between 1 and 100.
    pct_chance_hide = std::min<int>(pct_chance_hide, 100);
    pct_chance_hide = std::max<int>(pct_chance_hide, 1);
  }

  return pct_chance_hide;
}

int HidingCalculator::calculate_pct_chance_hidden_after_attacking(CreaturePtr creature)
{
  int pct_chance_hide = 0;

  if (creature != nullptr)
  {
    pct_chance_hide = creature->get_skills().get_value(SkillType::SKILL_GENERAL_HIDING) / HIDING_DIVISOR_AFTER_ATTACKING;
  }

  return pct_chance_hide;
}

int HidingCalculator::get_tod_hide_modifier_for_map_type(const TimeOfDayType tod, const MapType map_type) const
{
  int tod_mod = 0;

  switch (map_type)
  {
    case MapType::MAP_TYPE_COSMOS:
      tod_mod = -50;
      break;
    case MapType::MAP_TYPE_UNDERWATER:
      tod_mod = -20;
      break;
    case MapType::MAP_TYPE_UNDERWORLD:
      tod_mod = 10;
      break;
    case MapType::MAP_TYPE_OVERWORLD:
    {
      switch (tod)
      {
        case TimeOfDayType::TIME_OF_DAY_DAWN:
        case TimeOfDayType::TIME_OF_DAY_DUSK:
          tod_mod = 15;
          break;
        case TimeOfDayType::TIME_OF_DAY_NIGHT:
          tod_mod = 30;
          break;
        case TimeOfDayType::TIME_OF_DAY_DAY:
        case TimeOfDayType::TIME_OF_DAY_UNDEFINED:
          break;
      }
      break;
    }
    case MapType::MAP_TYPE_WORLD:
    default:
      break;
  }

  return tod_mod;
}

int HidingCalculator::get_viewing_creatures_modifier(CreaturePtr creature, MapPtr map, const vector<string>& creature_ids) const
{
  int cr_mod = 0;

  if (creature != nullptr && map != nullptr)
  {
    for (const string& id : creature_ids)
    {
      CreaturePtr view_cr = map->get_creature(id);

      if (view_cr != nullptr)
      {
        Coordinate c_coord = map->get_location(creature->get_id());
        Coordinate vc_coord = map->get_location(view_cr->get_id());
        int distance = CoordUtils::chebyshev_distance(c_coord, vc_coord);

        cr_mod -= view_cr->get_skills().get_value(SkillType::SKILL_GENERAL_DETECTION);
        cr_mod -= get_distance_modifier(distance);
      }
    }
  }

  return cr_mod;
}

// Creatures are easier to hide from if they are far away.
// The modifier makes it difficult to hide if there are
// several creatures close by.
int HidingCalculator::get_distance_modifier(const int dist) const
{
  int d_mod = 60 - (5 * dist);
  return d_mod;
}

#ifdef UNIT_TESTS
#include "unit_tests/HidingCalculator_test.cpp"
#endif


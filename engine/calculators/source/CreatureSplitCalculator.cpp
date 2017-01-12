#include "CreatureSplitCalculator.hpp"
#include "MapUtils.hpp"

const int CreatureSplitCalculator::BASE_MIN_CHANCE_SPLIT = 10;
const int CreatureSplitCalculator::HP_SPLIT_DIVISOR = 3;

int CreatureSplitCalculator::calculate_pct_chance_split(CreaturePtr creature, RacePtr race, MapPtr current_map)
{
  int chance_split = 0;

  if (creature != nullptr && race != nullptr)
  {
    bool race_splits = race->get_splits();
    Statistic hit_points = creature->get_hit_points();
    int cur_hp = hit_points.get_current();

    if (race_splits && cur_hp > (hit_points.get_base() / HP_SPLIT_DIVISOR) && !creature->get_is_player())
    {
      TileDirectionMap tdm = MapUtils::get_adjacent_tiles_to_creature(current_map, creature);
      bool tiles_ok = false;

      // Ensure there's an adjacent tile available to split into.
      for (const auto& tdm_pair : tdm)
      {
        if (MapUtils::is_tile_available_for_creature(creature, tdm_pair.second))
        {
          tiles_ok = true;
          break;
        }
      }
      
      if (tiles_ok)
      {
        // High level creatures have a greater chance to split.
        chance_split = static_cast<int>(creature->get_level().get_current() * 0.75);
        chance_split = std::max<int>(chance_split, BASE_MIN_CHANCE_SPLIT);
      }
    }
  }

  return chance_split;
}

// Split HP is always half of the current, with a minimum of 1.
int CreatureSplitCalculator::calculate_split_hit_points(CreaturePtr creature)
{
  int split_hp = 0;

  if (creature != nullptr)
  {
    split_hp = creature->get_hit_points().get_current() / 2;
    split_hp = std::max(split_hp, 1);
  }

  return split_hp;
}

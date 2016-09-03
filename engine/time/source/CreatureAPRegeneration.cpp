#include "CreatureAPRegeneration.hpp"
#include "RNG.hpp"
#include "StatisticsMarker.hpp"

const int CreatureAPRegeneration::PCT_CHANCE_MARK_STATISTIC = 5;

void CreatureAPRegeneration::tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature && !creature->is_ap_full())
  {
    // If any of them pass the check, regenerate an arcana point.
    uint minutes_per_ap = ap_regen_calc.calculate_minutes_per_ap_tick(creature, tile);
    
    if (total_minutes_elapsed % minutes_per_ap == 0)
    {
      int ap_incr = ap_regen_calc.calculate_ap_per_tick(creature);
      int cur = creature->get_arcana_points().get_current();
      int new_cur = creature->increment_arcana_points(ap_incr);

      if (new_cur > cur && RNG::percent_chance(PCT_CHANCE_MARK_STATISTIC))
      {
        StatisticsMarker sm;
        sm.mark_willpower(creature);
      }
    }
  }
}
;
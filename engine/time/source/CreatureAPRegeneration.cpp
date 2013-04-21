#include "CreatureAPRegeneration.hpp"

void CreatureAPRegeneration::tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature && !creature->is_ap_full())
  {
    // If any of them pass the check, regenerate an arcana point.
    uint minutes_per_ap = ap_regen_calc.calculate_minutes_per_arcana_point(creature);
    
    if (total_minutes_elapsed % minutes_per_ap == 0)
    {
      creature->increment_arcana_points(1);
    }
  }
}

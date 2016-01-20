#include "CreatureHPRegeneration.hpp"

void CreatureHPRegeneration::tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature && !creature->is_hp_full())
  {
    uint minutes_per_hp = hp_regen_calc.calculate_minutes_per_hp_tick(creature, tile);

    if (total_minutes_elapsed % minutes_per_hp == 0)
    {
      // If any of them pass the check, regenerate a hit point.
      int hp_incr = hp_regen_calc.calculate_hp_per_tick(creature);

      creature->increment_hit_points(hp_incr);
    }
  }
}

#include "Conversion.hpp"
#include "RangedCombatUtils.hpp"
#include "TileSelectionRangeChecker.hpp"

bool TileSelectionRangeChecker::is_selected_tile_in_range(CreaturePtr creature, const AttackType attack_type)
{
  bool in_range = false;

  // JCD FIXME: Once magic is implemented, break this off into separate
  // classes, and use a factory to instantiate the correct one.
  if (attack_type == AttackType::ATTACK_TYPE_RANGED)
  {
    if (creature)
    {
      MapPtr view_map = creature->get_decision_strategy()->get_fov_map();
      TargetMap target_map = creature->get_target_map();
      TargetMap::iterator t_it = target_map.find(std::to_string(static_cast<int>(attack_type)));

      // There should always be a target selected if we got this far in
      // the game logic.
      if (t_it != target_map.end() && view_map)
      {
        Coordinate c = t_it->second.second;
        in_range = RangedCombatUtils::is_coord_in_range(c, view_map);
      }
    }
  }

  return in_range;
}

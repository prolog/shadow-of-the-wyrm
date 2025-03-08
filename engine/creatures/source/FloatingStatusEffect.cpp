#include "Game.hpp"
#include "FloatingStatusEffect.hpp"
#include "MapUtils.hpp"
#include "MovementAccumulationUpdater.hpp"
#include "TerrainMovementAccumulationCheckerFactory.hpp"

bool FloatingStatusEffect::is_negative() const
{
  return false;
}

void FloatingStatusEffect::after_undo(CreaturePtr creature) const
{
  if (creature)
  {
    // This used to auto-kill, but maybe I've gotten softer in my middle
    // age. Disengage automatic movement and allow the player one turn
    /// to react.
    creature->get_automatic_movement_ref().set_engaged(false);
  }
}


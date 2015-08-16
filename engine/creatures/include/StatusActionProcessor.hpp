#pragma once
#include "Creature.hpp"
#include "ActionCost.hpp"

// Class used to process actions (particularly, action removal) after a
// creature has acted.  The main driver for this is that timewalking
// needs special handling - it needs to be removed when the creature takes
// a non-free action (attacking, etc), and has a chance to be removed when
// the creature takes its free movement.
class StatusActionProcessor
{
  public:
    void process_action(CreaturePtr creature, CreatureStatusMap statuses_before_action, ActionCost action);
};


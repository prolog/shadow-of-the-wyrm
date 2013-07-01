#include "PoisonStatusChange.hpp"
#include "StatusTypes.hpp"

void PoisonStatusChange::apply_change(CreaturePtr creature) const
{
  if (creature)
  {
    creature->set_status(StatusIdentifiers::STATUS_ID_POISON, true);
  }
}

void PoisonStatusChange::finalize_change(CreaturePtr creature) const
{
  // When poison runs its course, just remove the status ailment from
  // the creature.
  undo_change(creature);
}

void PoisonStatusChange::undo_change(CreaturePtr creature) const
{
  if (creature)
  {
    creature->remove_status(StatusIdentifiers::STATUS_ID_POISON);
  }
}

void PoisonStatusChange::tick() const
{
}


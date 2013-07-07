#include "CombatManager.hpp"
#include "Creature.hpp"
#include "PoisonStatusChange.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"

using namespace std;

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

void PoisonStatusChange::tick(CreaturePtr creature) const
{
  CreaturePtr no_creature;
  CombatManager cm;

  // Poison always deals a single point of damage per minute.
  cm.deal_damage(no_creature, creature, 1);
}


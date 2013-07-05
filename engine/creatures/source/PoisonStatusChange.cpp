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
}

bool PoisonStatusChange::has_status_message() const
{
  return true;
}

string PoisonStatusChange::get_status_message_sid() const
{
  string status_message = StatusAilmentTextKeys::STATUS_POISON;
  return status_message;
}

Colour PoisonStatusChange::get_status_message_colour() const
{
  return COLOUR_GREEN;
}




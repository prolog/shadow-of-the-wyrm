#include "Creature.hpp"
#include "Serialize.hpp"
#include "StatusChange.hpp"

using namespace std;

StatusChange::StatusChange()
{
}

StatusChange::~StatusChange()
{
}

void StatusChange::apply_change(CreaturePtr creature) const
{
}

void StatusChange::finalize_change(CreaturePtr creature) const
{
}

void StatusChange::undo_change(CreaturePtr creature) const
{
}

void StatusChange::tick(CreaturePtr creature) const
{
}

bool StatusChange::has_status_message() const
{
  return false;
}

string StatusChange::get_status_message_sid() const
{
  string no_message_sid;
  return no_message_sid;
}

Colour StatusChange::get_status_message_colour() const
{
  return COLOUR_WHITE;
}

#ifdef UNIT_TESTS
#include "unit_tests/StatusChange_test.cpp"
#endif

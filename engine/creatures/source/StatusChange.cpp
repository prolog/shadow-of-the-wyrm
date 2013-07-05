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

#ifdef UNIT_TESTS
#include "unit_tests/StatusChange_test.cpp"
#endif

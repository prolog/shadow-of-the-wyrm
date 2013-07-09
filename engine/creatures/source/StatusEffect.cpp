#include "Creature.hpp"
#include "Serialize.hpp"
#include "StatusEffect.hpp"

using namespace std;

StatusEffect::StatusEffect()
{
}

StatusEffect::~StatusEffect()
{
}

bool StatusEffect::should_apply_change(CreaturePtr creature) const
{
  return true;
}

void StatusEffect::apply_change(CreaturePtr creature) const
{
  before_apply(creature);
  apply(creature);
  after_apply(creature);
}

void StatusEffect::before_apply(CreaturePtr creature) const
{
}

void StatusEffect::apply(CreaturePtr creature) const
{
}

void StatusEffect::after_apply(CreaturePtr creature) const
{
}

string StatusEffect::get_player_application_message() const
{
  string no_message;
  return no_message;
}

void StatusEffect::finalize_change(CreaturePtr creature) const
{
  before_finalize(creature);
  finalize(creature);
  after_finalize(creature);
}

void StatusEffect::before_finalize(CreaturePtr creature) const
{
}

void StatusEffect::finalize(CreaturePtr creature) const
{
}

string StatusEffect::get_player_finalize_message() const
{
  string no_message;
  return no_message;
}

void StatusEffect::after_finalize(CreaturePtr creature) const
{
}

void StatusEffect::undo_change(CreaturePtr creature) const
{
  before_undo(creature);
  undo(creature);
  after_undo(creature);
}

void StatusEffect::before_undo(CreaturePtr creature) const
{
}

void StatusEffect::undo(CreaturePtr creature) const
{
}

void StatusEffect::after_undo(CreaturePtr creature) const
{
}

string StatusEffect::get_player_undo_message() const
{
  string no_message;
  return no_message;
}

void StatusEffect::tick(CreaturePtr creature) const
{
}

#ifdef UNIT_TESTS
#include "unit_tests/StatusEffect_test.cpp"
#endif

#include "DefaultNPCMagicDecision.hpp"

using namespace std;

// Optimistic: if the creature *can* cast it, cast it!
pair<bool, Direction> DefaultNPCMagicDecision::decide(CreaturePtr caster, MapPtr view_map, const Spell& spell, const set<string>& creature_threats) const
{
  bool decision = false;

  if (caster != nullptr)
  {
    decision = true;
  }

  return make_pair(decision, Direction::DIRECTION_NULL);
}

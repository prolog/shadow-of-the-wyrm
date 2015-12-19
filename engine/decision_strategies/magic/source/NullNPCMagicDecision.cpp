#include "NullNPCMagicDecision.hpp"

using namespace std;

pair<bool, Direction> NullNPCMagicDecision::decide(CreaturePtr caster, MapPtr view_map, const Spell& spell, const set<string>& creature_threats) const
{
  return make_pair(false, Direction::DIRECTION_NULL);
}


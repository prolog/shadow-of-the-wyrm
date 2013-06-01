#include "CombatManager.hpp"
#include "SpellFailureConsequences.hpp"

using namespace std;

// The spellbook erupts in flames, dealing some amount of damage to the
// caster, and destroying the spellbook.
bool SpellFailureConsequences::damage_caster(CreaturePtr caster)
{
  bool spellbook_destroyed = false;

  float damage_pct = get_damage_pct();
  uint damage_in_hp = static_cast<uint>(caster->get_hit_points().get_current() * damage_pct);
  string spellbook_message_sid = get_damage_message_sid();

  // Marginal spell failures do nothing, so check to see if the creature's
  // actually been damaged.
  if (damage_in_hp > 0)
  {
    CombatManager cm;
    CreaturePtr no_attacker;
    cm.deal_damage(no_attacker, caster, damage_in_hp, spellbook_message_sid);

    spellbook_destroyed = true;
  }

  return spellbook_destroyed;
}

bool SpellFailureConsequences::inflict_status_ailments(CreaturePtr caster)
{
  return false;
}

bool SpellFailureConsequences::summon_creatures(CreaturePtr caster)
{
  return false;
}


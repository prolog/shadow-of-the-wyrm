#include "CombatManager.hpp"
#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "DeathSourceTextKeys.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SpellFailureConsequences.hpp"

using namespace std;

// The spellbook erupts in flames, dealing some amount of damage to the
// caster, and destroying the spellbook.
bool SpellFailureConsequences::damage_caster(CreaturePtr caster)
{
  bool spellbook_destroyed = false;

  float damage_pct = get_damage_pct();
  int damage_in_hp = static_cast<int>(caster->get_hit_points().get_current() * damage_pct);
  Damage damage_default;
  damage_default.set_modifier(damage_in_hp);
  string source_id; // nobody gets exp for the spellbook erupting and dealing damage.
  string spellbook_message_sid = get_damage_message_sid();

  // Marginal spell failures do nothing, so check to see if the creature's
  // actually been damaged.
  if (damage_in_hp > 0)
  {
    CombatManager cm;
    CreaturePtr no_attacker;
    cm.deal_damage(no_attacker, caster, AttackType::ATTACK_TYPE_MAGICAL, source_id, damage_in_hp, damage_default, spellbook_message_sid, DeathSourceTextKeys::DEATH_SOURCE_INCINERATION);

    spellbook_destroyed = true;
  }

  return spellbook_destroyed;
}

bool SpellFailureConsequences::inflict_status_ailments(CreaturePtr /*caster*/)
{
  return false;
}

bool SpellFailureConsequences::summon_creatures(CreaturePtr caster)
{
  MapPtr map = Game::instance().get_current_map();
  GameUtils::summon_creatures(caster, map, get_summoned_creature_details(), get_summoned_creatures_message_sid());

  return false;
}


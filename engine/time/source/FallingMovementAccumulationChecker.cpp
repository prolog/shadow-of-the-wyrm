#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "DeathSourceTextKeys.hpp"
#include "FallingMovementAccumulationChecker.hpp"

using namespace std;

// Falling from a great distance is insta-death.
void FallingMovementAccumulationChecker::check(CreaturePtr creature)
{
  if (creature)
  {
    string falling_message_sid;
    
    if (creature->get_is_player())
    {
      falling_message_sid = ActionTextKeys::ACTION_PLAYER_FALLING;
    }

    CombatManager cm;
    CreaturePtr no_attacker;
    int falling_damage = creature->get_hit_points().get_current() + 10;
    Damage falling_default;
    falling_default.set_modifier(falling_damage);

    cm.deal_damage(no_attacker, creature, AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED, "", falling_damage, falling_default, falling_message_sid, DeathSourceTextKeys::DEATH_SOURCE_FALLING);
  }
}

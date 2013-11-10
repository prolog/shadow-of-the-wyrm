#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "Mountaineering.hpp"
#include "MountainClimbingCalculator.hpp"
#include "SkillManager.hpp"

using std::string;

void Mountaineering::check_for_fall(CreaturePtr creature)
{
  if (creature)
  {
    SkillManager sm;
    MountainClimbingCalculator mcc;

    int mountaineering_skill_value = sm.get_skill_value(creature, SKILL_GENERAL_MOUNTAINEERING);
    
    if (mcc.generate_does_fall_from_exhaustion(mountaineering_skill_value, creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL)))
    {
      string fall_message_sid;
      
      if (creature->get_is_player())
      {
        fall_message_sid = ActionTextKeys::ACTION_PLAYER_FALL_FROM_MOUNTAIN;
      }
      
      CombatManager cm;
      CreaturePtr no_attacker;
      cm.deal_damage(no_attacker, creature, mcc.generate_falling_damage(), fall_message_sid);

      // Reset counter, since we're no longer "on" the mt.
      creature->get_movement_accumulation_ref().set_minutes_on_tile_type_given_movement(0); 
    }
  }
}


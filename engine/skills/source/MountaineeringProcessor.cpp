#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "MountaineeringProcessor.hpp"
#include "MountainClimbingCalculator.hpp"
#include "SkillManager.hpp"

using std::string;

ActionCostValue MountaineeringProcessor::process(CreaturePtr creature, MapPtr map /* unused, will be nullptr */)
{
  if (creature)
  {
    SkillManager sm;
    MountainClimbingCalculator mcc;

    int mountaineering_skill_value = sm.get_skill_value(creature, SkillType::SKILL_GENERAL_MOUNTAINEERING);
    
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
    else
    {
      creature->get_skills().mark(SkillType::SKILL_GENERAL_MOUNTAINEERING);
    }
  }

  return get_default_skill_action_cost_value(creature);
}


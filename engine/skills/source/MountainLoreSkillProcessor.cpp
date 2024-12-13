#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "DeathSourceTextKeys.hpp"
#include "MountainLoreSkillProcessor.hpp"
#include "MountainClimbingCalculator.hpp"
#include "SkillManager.hpp"

using std::string;

ActionCostValue MountainLoreSkillProcessor::process(CreaturePtr creature, MapPtr /*map*/)
{
  if (creature)
  {
    SkillManager sm;
    MountainClimbingCalculator mcc;

    int mountain_lore_skill_value = sm.get_skill_value(creature, SkillType::SKILL_GENERAL_MOUNTAIN_LORE);
    
    if (mcc.generate_does_fall_from_exhaustion(mountain_lore_skill_value, creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL)))
    {
      string fall_message_sid;
      
      if (creature->get_is_player())
      {
        fall_message_sid = ActionTextKeys::ACTION_PLAYER_FALL_FROM_MOUNTAIN;
      }
      
      CombatManager cm;
      CreaturePtr no_attacker;
      int falling_damage = mcc.generate_falling_damage();
      Damage falling_default;
      falling_default.set_modifier(falling_damage);

      cm.deal_damage(no_attacker, creature, AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED, "", falling_damage, falling_default, fall_message_sid, DeathSourceTextKeys::DEATH_SOURCE_FALLING);

      // Reset counter, since we're no longer "on" the mt.
      creature->get_movement_accumulation_ref().set_minutes_on_tile_type_given_movement(0); 
    }
    else
    {
      creature->get_skills().mark(SkillType::SKILL_GENERAL_MOUNTAIN_LORE);
    }
  }

  return get_default_skill_action_cost_value(creature);
}

SkillProcessorPtr MountainLoreSkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<MountainLoreSkillProcessor>();
  return proc;
}

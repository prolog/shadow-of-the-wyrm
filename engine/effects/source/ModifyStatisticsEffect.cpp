#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "ModifyStatisticsEffect.hpp"

using namespace std;

void ModifyStatisticsEffect::set_statistics_modifier(const StatisticsModifier& new_sm)
{
  sm = new_sm;
}

StatisticsModifier ModifyStatisticsEffect::get_statistics_modifier() const
{
  return sm;
}

string ModifyStatisticsEffect::get_effect_identification_message(std::shared_ptr<Creature> creature) const
{
  string creature_desc_sid;
  bool is_player = false;
  
  if (creature)
  {
    creature_desc_sid = creature->get_description_sid();
    is_player = creature->get_is_player();
  }
  
  return EffectTextKeys::get_modify_statistics_effect_message(creature_desc_sid, is_player);
}

Effect* ModifyStatisticsEffect::clone()
{
  return new ModifyStatisticsEffect(*this);
}

bool ModifyStatisticsEffect::apply_statistics_modifiers(CreaturePtr creature, const StatisticsModifier& sm) const
{
  if (creature)
  {
  }

  return true;
}

bool ModifyStatisticsEffect::effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am)
{
  vector<int> blessed_sm_v = sm.get_raw_values();
  std::transform(blessed_sm_v.begin(), blessed_sm_v.end(), blessed_sm_v.begin(), 
  [](int a)
    {
      if (a > 0)
      {
        return a * 2;
      }
      else
      {
        return a / 2;
      }
  });

  StatisticsModifier blessed_sm(blessed_sm_v);
  return apply_statistics_modifiers(creature, blessed_sm);
}

bool ModifyStatisticsEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return apply_statistics_modifiers(creature, sm);
}

bool ModifyStatisticsEffect::effect_cursed(CreaturePtr creature, ActionManager * const am)
{
  vector<int> blessed_sm_v = sm.get_raw_values();
  std::transform(blessed_sm_v.begin(), blessed_sm_v.end(), blessed_sm_v.begin(),
  [](int a)
  {
    if (a < 0)
    {
      return a * 2;
    }
    else
    {
      return a / 2;
    }
  });

  StatisticsModifier blessed_sm(blessed_sm_v);
  return apply_statistics_modifiers(creature, blessed_sm);
}



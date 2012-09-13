#include "Creature.hpp"
#include "HealingEffect.hpp"
#include "RNG.hpp"

using std::string;

const float HealingEffect::BLESSED_MULTIPLIER = 2.0;
const float HealingEffect::UNCURSED_MULTIPLIER = 1.0;
const float HealingEffect::CURSED_MULTIPLIER = 0.5;
const int HealingEffect::BASE_MIN_HP = 5;
const int HealingEffect::BASE_MAX_HP = 30;

string HealingEffect::get_effect_identification_message(boost::shared_ptr<Creature> creature) const
{
  string creature_desc_sid;
  bool is_player = false;
  
  if (creature)
  {
    creature_desc_sid = creature->get_description_sid();
    is_player = creature->get_is_player();
  }
  
  return EffectTextKeys::get_healing_effect_message(creature_desc_sid, is_player);
}

Effect* HealingEffect::clone()
{
  return new HealingEffect(*this);
}

bool HealingEffect::heal(CreaturePtr creature, const float healing_multiplier) const
{
  bool effect_identified = false;

  if (creature)
  {
    int healing_amount = get_random_healing_amount() * healing_multiplier;

    Statistic hit_points = creature->get_hit_points();

    int base_hp = hit_points.get_base();
    int current_hp = hit_points.get_current();
    
    if (current_hp < base_hp)
    {
      hit_points.set_current(std::min(base_hp, (current_hp + healing_amount)));
      creature->set_hit_points(hit_points);
      
      // Some healing was performed, so the effect was identified.
      effect_identified = true;
    }
  }

  return effect_identified;
}

bool HealingEffect::effect_blessed(boost::shared_ptr<Creature> creature)
{
  return heal(creature, BLESSED_MULTIPLIER);
}

bool HealingEffect::effect_uncursed(CreaturePtr creature)
{
  return heal(creature, UNCURSED_MULTIPLIER);
}

bool HealingEffect::effect_cursed(CreaturePtr creature)
{
  return heal(creature, CURSED_MULTIPLIER);
}

int HealingEffect::get_random_healing_amount() const
{
  return RNG::range(BASE_MIN_HP, BASE_MAX_HP);
}

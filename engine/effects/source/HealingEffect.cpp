#include "Creature.hpp"
#include "HealingEffect.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"

using namespace std;

const double HealingEffect::BLESSED_MULTIPLIER = 2.0;
const double HealingEffect::UNCURSED_MULTIPLIER = 1.0;
const double HealingEffect::CURSED_MULTIPLIER = 0.5;
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

bool HealingEffect::heal(CreaturePtr creature, const double healing_multiplier) const
{
  bool effect_identified = false;

  if (creature)
  {
    int healing_amount = static_cast<int>(get_random_healing_amount() * healing_multiplier);

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

bool HealingEffect::effect_blessed(boost::shared_ptr<Creature> creature, ActionManager * const am)
{
  return heal(creature, BLESSED_MULTIPLIER);
}

bool HealingEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return heal(creature, UNCURSED_MULTIPLIER);
}

bool HealingEffect::effect_cursed(CreaturePtr creature, ActionManager * const am)
{
  return heal(creature, CURSED_MULTIPLIER);
}

int HealingEffect::get_random_healing_amount() const
{
  return RNG::range(BASE_MIN_HP, BASE_MAX_HP);
}

bool HealingEffect::serialize(ostream& stream)
{
  Effect::serialize(stream);

  Serialize::write_double(stream, BLESSED_MULTIPLIER);
  Serialize::write_double(stream, UNCURSED_MULTIPLIER);
  Serialize::write_double(stream, CURSED_MULTIPLIER);
  Serialize::write_int(stream, BASE_MIN_HP);
  Serialize::write_int(stream, BASE_MAX_HP);

  return true;
}

bool HealingEffect::deserialize(istream& stream)
{
  Effect::deserialize(stream);

  double& bmult = const_cast<double&>(BLESSED_MULTIPLIER);
  double& umult = const_cast<double&>(UNCURSED_MULTIPLIER);
  double& cmult = const_cast<double&>(CURSED_MULTIPLIER);
  int& min      = const_cast<int&>(BASE_MIN_HP);
  int& max      = const_cast<int&>(BASE_MAX_HP);

  Serialize::read_double(stream, bmult);
  Serialize::read_double(stream, umult);
  Serialize::read_double(stream, cmult);
  Serialize::read_int(stream, min);
  Serialize::read_int(stream, max);

  return true;
}

ClassIdentifier HealingEffect::internal_class_identifier() const
{
  return CLASS_ID_HEALING_EFFECT;
}
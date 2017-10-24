#include "Conversion.hpp"
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "Log.hpp"
#include "HealingEffect.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"

using namespace std;

const double HealingEffect::BLESSED_MULTIPLIER = 2.0;
const double HealingEffect::UNCURSED_MULTIPLIER = 1.0;
const double HealingEffect::CURSED_MULTIPLIER = 0.5;
const int HealingEffect::BASE_MIN_HP = 5;
const int HealingEffect::BASE_MAX_HP = 30;
const string HealingEffect::HEALING_MIN = "HEALING_MIN";
const string HealingEffect::HEALING_MAX = "HEALING_MAX";

HealingEffect::HealingEffect()
  : min_hp(BASE_MIN_HP), max_hp(BASE_MAX_HP)
{
}

string HealingEffect::get_effect_identification_message(std::shared_ptr<Creature> creature) const
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

bool HealingEffect::effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return heal(creature, BLESSED_MULTIPLIER);
}

bool HealingEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return heal(creature, UNCURSED_MULTIPLIER);
}

bool HealingEffect::effect_cursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return heal(creature, CURSED_MULTIPLIER);
}

int HealingEffect::get_random_healing_amount() const
{
  return RNG::range(min_hp, max_hp);
}

void HealingEffect::read_properties(const map<string, string>& properties)
{
  auto p_it_min = properties.find(HEALING_MIN);
  auto p_it_max = properties.find(HEALING_MAX);

  if (p_it_min != properties.end())
  {
    try
    {
      min_hp = String::to_int(p_it_min->second);
    }
    catch (...)
    {
      Log::instance().error("Could not convert min healing value!");
    }
  }

  if (p_it_max != properties.end())
  {
    try
    {
      max_hp = String::to_int(p_it_max->second);
    }
    catch (...)
    {
      Log::instance().error("Could not convert max healing value!");
    }
  }
}
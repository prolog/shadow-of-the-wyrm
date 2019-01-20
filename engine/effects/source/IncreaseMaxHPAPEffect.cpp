#include "IncreaseMaxHPAPEffect.hpp"
#include "Conversion.hpp"
#include "EffectTextKeys.hpp"

using namespace std;
// HPAP common code
const int IncreaseMaxHPAPEffect::INCR_AMOUNT_BLESSED = 4;
const int IncreaseMaxHPAPEffect::INCR_AMOUNT_UNCURSED = 2;
const int IncreaseMaxHPAPEffect::INCR_AMOUNT_CURSED = 1;

bool IncreaseMaxHPAPEffect::effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return increase(creature, INCR_AMOUNT_BLESSED);
}

bool IncreaseMaxHPAPEffect::effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return increase(creature, INCR_AMOUNT_UNCURSED);
}

bool IncreaseMaxHPAPEffect::effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return increase(creature, INCR_AMOUNT_CURSED);
}

bool IncreaseMaxHPAPEffect::increase(CreaturePtr creature, int incr_amount)
{
  bool eff_ident = false;

  if (creature != nullptr)
  {
    string check_prop_name = get_check_property();
    Statistic& check_stat = get_check_statistic(creature);
    Statistic& inc_stat = get_increase_statistic(creature);

    if (can_increase(creature, check_stat))
    {
      increase_stat(creature, inc_stat, incr_amount);
      eff_ident = true;
    }
  }

  return eff_ident;
}

bool IncreaseMaxHPAPEffect::can_increase(CreaturePtr creature, const Statistic& stat) const
{
  if (creature != nullptr)
  {
    string check_prop_name = get_check_property();
    string num_increments_s = creature->get_additional_property(check_prop_name);
    int num_increments = num_increments_s.empty() ? 0 : String::to_int(num_increments_s);

    return (num_increments < stat.get_base());
  }

  return false;
}

void IncreaseMaxHPAPEffect::increase_stat(CreaturePtr creature, Statistic& inc_stat, const int incr_amount)
{
  if (creature != nullptr)
  {
    string check_prop_name = get_check_property();
    string num_increments_s = creature->get_additional_property(check_prop_name);
    int num_increments = num_increments_s.empty() ? 0 : String::to_int(num_increments_s);

    inc_stat.set_base(inc_stat.get_base() + incr_amount);
    inc_stat.set_current(inc_stat.get_current() + incr_amount);
    ++num_increments;

    creature->set_additional_property(check_prop_name, to_string(num_increments));
  }
}

// HP
string IncreaseMaxHPEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string creature_desc_sid;
  bool is_player = false;

  if (creature)
  {
    creature_desc_sid = creature->get_description_sid();
    is_player = creature->get_is_player();
  }

  return EffectTextKeys::get_increase_max_hp_effect_message(creature_desc_sid, is_player);
}

Effect* IncreaseMaxHPEffect::clone()
{
  return new IncreaseMaxHPEffect(*this);
}

Statistic& IncreaseMaxHPEffect::get_check_statistic(CreaturePtr creature)
{
  return creature->get_health_ref();
}

Statistic& IncreaseMaxHPEffect::get_increase_statistic(CreaturePtr creature)
{
  return creature->get_hit_points_ref();
}

string IncreaseMaxHPEffect::get_check_property() const
{
  return "increase_max_hp_increments";
}

// AP
string IncreaseMaxAPEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string creature_desc_sid;
  bool is_player = false;

  if (creature)
  {
    creature_desc_sid = creature->get_description_sid();
    is_player = creature->get_is_player();
  }

  return EffectTextKeys::get_increase_max_ap_effect_message(creature_desc_sid, is_player);
}

Effect* IncreaseMaxAPEffect::clone()
{
  return new IncreaseMaxAPEffect(*this);
}

Statistic& IncreaseMaxAPEffect::get_check_statistic(CreaturePtr creature)
{
  return creature->get_willpower_ref();
}

Statistic& IncreaseMaxAPEffect::get_increase_statistic(CreaturePtr creature)
{
  return creature->get_arcana_points_ref();
}

string IncreaseMaxAPEffect::get_check_property() const
{
  return "increase_max_ap_increments";
}
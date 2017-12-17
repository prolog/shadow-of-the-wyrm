#include "CurrentCreatureAbilities.hpp"
#include "EvadeCalculator.hpp"
#include "StatusEffectFactory.hpp"
#include "Wearable.hpp"

using namespace std;

EvadeCalculator::EvadeCalculator()
{
}

EvadeCalculator::~EvadeCalculator()
{
}

// Evade = equipment bonuses/penalties
//       + 1 point for every two points of Agility over 10
//       - 1 point for every two points of Agility under 10
//       - 1 point per level if enraged
//       + any bonuses or penalties from modifiers
int EvadeCalculator::calculate_evade(const CreaturePtr& c)
{
  int evade = 0;
  
  if (c)
  {
    evade = c->get_base_evade().get_current();
    
    int agility = c->get_agility().get_current();
    int agility_bonus = (agility - 10) / 2;
    
    evade += get_equipment_bonus(c);
    evade += get_modifier_bonus(c);
    evade += get_skill_bonus(c);
    evade -= get_rage_penalty(c);
    evade += agility_bonus;
  }
  
  return evade;
}

int EvadeCalculator::get_equipment_bonus(const CreaturePtr& c)
{
  int equipment_evade_bonus = 0;
  
  Equipment& eq = c->get_equipment();
  EquipmentMap equipment = eq.get_equipment();
  
  for(EquipmentMap::value_type& item : equipment)
  {
    WearablePtr equipped = dynamic_pointer_cast<Wearable>(item.second);
    
    if (equipped)
    {
      // The player can equip a lot of things in the ammunition slot.  But the
      // evade bonus is only granted if the item is actually ammunition.  This
      // prevents sneaky things like shoving an additional shield in that slot
      // purely for the Ev (nerf!)
      if (item.first == EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION)
      {
        if (equipped->get_type() == ItemType::ITEM_TYPE_AMMUNITION)
        {
          equipment_evade_bonus += equipped->get_evade();
        }
      }
      else
      {
        equipment_evade_bonus += equipped->get_evade();
      }
    }
  }
  
  return equipment_evade_bonus;
}

int EvadeCalculator::get_modifier_bonus(const CreaturePtr& c)
{
  int mod_bonus = 0;

  if (c)
  {
    const map<double, vector<pair<string, Modifier>>> modifiers = c->get_active_modifiers();

    for (const auto& mod_pair : modifiers)
    {
      for (const auto& current_mod_pair : mod_pair.second)
      {
        mod_bonus += current_mod_pair.second.get_evade_modifier();
      }
    }
  }

  return mod_bonus;
}

int EvadeCalculator::get_skill_bonus(const CreaturePtr& c)
{
  int sk_bonus = 0;

  if (c != nullptr)
  {
    // +1 to evade for every four points of Blindfighting, if the creature is
    // blind.
    CurrentCreatureAbilities cca;

    if (!cca.can_see(c, false))
    {
      int blindfighting_value = c->get_skills().get_value_incr_marks(SkillType::SKILL_GENERAL_BLIND_FIGHTING);
      sk_bonus += (blindfighting_value / 4);
    }
  }

  return sk_bonus;
}

int EvadeCalculator::get_rage_penalty(const CreaturePtr& c)
{
  int penalty = 0;

  if (c != nullptr)
  {
    if (c->has_status(StatusIdentifiers::STATUS_ID_RAGE))
    {
      penalty = c->get_level().get_current();
    }
  }

  return penalty;
}

#ifdef UNIT_TESTS
#include "unit_tests/EvadeCalculator_test.cpp"
#endif

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
    const map<double, vector<pair<string, Modifier>>>& modifiers = c->get_modifiers_ref();

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

#ifdef UNIT_TESTS
#include "unit_tests/EvadeCalculator_test.cpp"
#endif

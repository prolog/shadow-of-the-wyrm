#include <boost/foreach.hpp>
#include "EvadeCalculator.hpp"
#include "StatusEffectFactory.hpp"
#include "Wearable.hpp"

using std::string;
using boost::dynamic_pointer_cast;

EvadeCalculator::EvadeCalculator()
{
}

EvadeCalculator::~EvadeCalculator()
{
}

// Evade = equipment bonuses/penalties
//       + 1 point for every two points of Agility over 10
//       - 1 point for every two points of Agility under 10
//       + 1 point for every 5 points of Valour under 50
//       - 1 point for every 5 points of Valour over 50
//       + any bonuses or penalties from status ailments
int EvadeCalculator::calculate_evade(const CreaturePtr& c)
{
  int evade = 0;
  
  if (c)
  {
    evade = c->get_base_evade().get_current();
    
    int agility = c->get_agility().get_current();
    int valour  = c->get_valour().get_current();

    int agility_bonus = (agility - 10) / 2;
    int valour_bonus = (valour - 50) / 5;
    int status_bonus = get_status_bonus(c);
    
    evade += get_equipment_bonus(c);
    evade += agility_bonus;
    evade += status_bonus;
    evade -= valour_bonus;
  }
  
  return evade;
}

int EvadeCalculator::get_equipment_bonus(const CreaturePtr& c)
{
  int equipment_evade_bonus = 0;
  
  Equipment& eq = c->get_equipment();
  EquipmentMap equipment = eq.get_equipment();
  
  BOOST_FOREACH(EquipmentMap::value_type& item, equipment)
  {
    WearablePtr equipped = dynamic_pointer_cast<Wearable>(item.second);
    
    if (equipped)
    {
      equipment_evade_bonus += equipped->get_evade();
    }
  }
  
  return equipment_evade_bonus;
}

int EvadeCalculator::get_status_bonus(const CreaturePtr& c)
{
  int status_bonus = 0;

  CreatureStatusMap status = c->get_statuses();

  BOOST_FOREACH(CreatureStatusMap::value_type& status_pair, status)
  {
    string status_id = status_pair.first;
    bool status_applied = status_pair.second;

    if (status_applied)
    {
      StatusEffectPtr status_effect = StatusEffectFactory::create_status_effect(status_id);
      status_bonus += status_effect->get_evade_bonus(c);
    }
  }

  return status_bonus;
}

#ifdef UNIT_TESTS
#include "unit_tests/EvadeCalculator_test.cpp"
#endif

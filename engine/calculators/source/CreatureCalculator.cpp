#include "CreatureCalculator.hpp"
#include "CreatureToHitCalculator.hpp"
#include "CreatureAdditionalDamageCalculator.hpp"
#include "EvadeCalculator.hpp"
#include "RaceManager.hpp"
#include "ClassManager.hpp"
#include "ResistancesCalculator.hpp"
#include "SoakCalculator.hpp"

CreatureCalculator::CreatureCalculator()
{
}

CreatureCalculator::~CreatureCalculator()
{
}

void CreatureCalculator::update_calculated_values(const CreaturePtr& c)
{
  if (c)
  {
    // Evade
    int calc_evade = EvadeCalculator::calculate_evade(c);
    c->set_evade(calc_evade);

    // Soak
    int calc_soak = SoakCalculator::calculate_soak(c);
    c->set_soak(calc_soak);

    // To-Hit from additional sources
    CreatureToHitCalculator cthc;
    int calc_to_hit = cthc.calculate_to_hit(c);
    c->set_to_hit(calc_to_hit);

    // Damage from additional sources
    CreatureAdditionalDamageCalculator cadc;
    int calc_addl_damage = cadc.calculate_additional_damage(c);
    c->set_addl_damage(calc_addl_damage);

    // Resistances
    RaceManager rm;
    ClassManager cm;
    ResistancesCalculator rc;
    Resistances resists = rc.calculate_resistances(c, rm.get_race(c->get_race_id()), cm.get_class(c->get_class_id()));
    c->set_resistances(resists);
  }
}

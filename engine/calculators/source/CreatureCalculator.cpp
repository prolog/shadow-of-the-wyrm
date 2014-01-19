#include "CreatureCalculator.hpp"
#include "CreatureToHitCalculator.hpp"
#include "CreatureAdditionalDamageCalculator.hpp"
#include "EvadeCalculator.hpp"
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
  }
}

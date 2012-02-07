#include "CreatureCalculator.hpp"
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
  }
}

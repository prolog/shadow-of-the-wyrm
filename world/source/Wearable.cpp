#include "Wearable.hpp"

Wearable::Wearable()
: evade(0), soak(0)
{
}

Wearable::~Wearable()
{
}

void Wearable::set_evade(const int new_evade)
{
  evade = new_evade;
}

int Wearable::get_evade() const
{
  return evade;
}

void Wearable::set_soak(const int new_soak)
{
  soak = new_soak;
}

int Wearable::get_soak() const
{
  return soak;
}


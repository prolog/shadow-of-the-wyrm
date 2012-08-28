#include "Wearable.hpp"

using boost::dynamic_pointer_cast;

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

bool Wearable::additional_item_attributes_match(boost::shared_ptr<Item> i)
{
  bool match = (i);
  WearablePtr i_wear = dynamic_pointer_cast<Wearable>(i);
  
  match = i_wear;
  
  if (i_wear)
  {
    match &= (evade == i_wear->get_evade());
    match &= (soak  == i_wear->get_soak() );
  }
  
  return match;
}

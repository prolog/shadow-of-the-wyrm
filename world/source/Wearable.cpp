#include "Serialize.hpp"
#include "Wearable.hpp"

using namespace std;
using std::dynamic_pointer_cast;

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

bool Wearable::additional_item_attributes_match(std::shared_ptr<Item> i)
{
  bool match = (i != nullptr);
  WearablePtr i_wear = dynamic_pointer_cast<Wearable>(i);
  
  match = i_wear != nullptr;
  
  if (i_wear)
  {
    match = match && (evade == i_wear->get_evade());
    match = match && (soak  == i_wear->get_soak() );
  }
  
  return match;
}

bool Wearable::serialize(ostream& stream) const
{
  Item::serialize(stream);
  Serialize::write_int(stream, evade);
  Serialize::write_int(stream, soak);

  return true;
}

bool Wearable::deserialize(istream& stream)
{
  Item::deserialize(stream);
  Serialize::read_int(stream, evade);
  Serialize::read_int(stream, soak);

  return true;
}
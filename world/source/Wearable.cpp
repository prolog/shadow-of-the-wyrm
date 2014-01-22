#include <sstream>
#include "Serialize.hpp"
#include "Wearable.hpp"

using namespace std;
using std::dynamic_pointer_cast;

Wearable::Wearable()
: evade(0), soak(0), to_hit(0), addl_damage(0)
{
}

Wearable::~Wearable()
{
}

void Wearable::set_to_hit(const int new_to_hit)
{
  to_hit = new_to_hit;
}

int Wearable::get_to_hit() const
{
  return to_hit;
}

void Wearable::set_addl_damage(const int new_addl_damage)
{
  addl_damage = new_addl_damage;
}

int Wearable::get_addl_damage() const
{
  return addl_damage;
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

string Wearable::get_synopsis() const
{
  stringstream ss;

  if (to_hit > 0 || addl_damage > 0)
  {
    ss << "(" << to_hit << ", " << addl_damage << ") ";
  }
  
  if (evade > 0 || soak > 0)
  {
    ss << "[" << evade << ", " << soak << "]";
  }

  return ss.str();
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
    match = match && (to_hit == i_wear->get_to_hit());
    match = match && (addl_damage == i_wear->get_addl_damage());
  }
  
  return match;
}

bool Wearable::serialize(ostream& stream) const
{
  Item::serialize(stream);
  Serialize::write_int(stream, evade);
  Serialize::write_int(stream, soak);
  Serialize::write_int(stream, to_hit);
  Serialize::write_int(stream, addl_damage);

  return true;
}

bool Wearable::deserialize(istream& stream)
{
  Item::deserialize(stream);
  Serialize::read_int(stream, evade);
  Serialize::read_int(stream, soak);
  Serialize::read_int(stream, to_hit);
  Serialize::read_int(stream, addl_damage);

  return true;
}

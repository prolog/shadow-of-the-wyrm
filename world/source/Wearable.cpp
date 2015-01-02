#include <sstream>
#include "RNG.hpp"
#include "Serialize.hpp"
#include "Wearable.hpp"

using namespace std;
using std::dynamic_pointer_cast;

// Local enumeration for wearable to determine exactly how a wearable
// is enchanted.
enum struct ImproveWearableType
{
  IMPROVE_WEARABLE_EVADE = 1,
  IMPROVE_WEARABLE_SOAK  = 2,
  IMPROVE_WEARABLE_BOTH  = 3
};

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

void Wearable::do_enchant_item(const int points)
{
  if (RNG::percent_chance(50))
  {
    Item::do_enchant_item(points);
  }

  do_improve_item(points);
}


void Wearable::do_smith_item(const int points)
{
  if (RNG::percent_chance(25))
  {
    Item::do_smith_item(points);
  }

  do_improve_item(points);
}

void Wearable::do_improve_item(const int points)
{
  ImproveWearableType wearable_improve = static_cast<ImproveWearableType>(RNG::range(IMPROVE_WEARABLE_EVADE, IMPROVE_WEARABLE_BOTH));

  switch (wearable_improve)
  {
  case IMPROVE_WEARABLE_EVADE:
    set_evade(get_evade() + static_cast<int>((points * 1.5)));
    break;
  case IMPROVE_WEARABLE_SOAK:
    set_soak(get_soak() + points);
    break;
  case IMPROVE_WEARABLE_BOTH:
    set_evade(get_evade() + points);
    set_soak(get_soak() + (points / 2));
    break;
  }
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

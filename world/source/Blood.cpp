#include "global_prototypes.hpp"
#include "Blood.hpp"
#include "Serialize.hpp"

using namespace std;

const float Blood::DEFAULT_LITRES_OF_BLOOD = 5.0f;
unordered_map<CreatureSize, float> Blood::litres_by_size_map;

Blood::Blood()
: litres(DEFAULT_LITRES_OF_BLOOD), grams_alcohol(0.0f), blood_alcohol_content(0.0f)
{
  if (litres_by_size_map.empty())
  {
    initialize_litres_by_size_map();
  }
}

Blood::Blood(CreatureSize c_size)
{
  if (litres_by_size_map.empty())
  {
    initialize_litres_by_size_map();
  }

  auto bl_it = litres_by_size_map.find(c_size);

  if (bl_it != litres_by_size_map.end())
  {
    litres = bl_it->second;
  }

  grams_alcohol = 0.0f;
  blood_alcohol_content = 0.0f;
}

bool Blood::operator==(const Blood& b) const
{
  bool result = true;

  result = result && (litres == b.litres);
  result = result && (fequal(grams_alcohol, b.grams_alcohol));
  result = result && (fequal(blood_alcohol_content, b.blood_alcohol_content));

  return result;
}

void Blood::initialize_litres_by_size_map()
{
  litres_by_size_map.empty();

  litres_by_size_map = std::unordered_map<CreatureSize, float>{ 
                       {CREATURE_SIZE_TINY, 0.5f}, 
                       {CREATURE_SIZE_SMALL, 2.5f}, 
                       {CREATURE_SIZE_MEDIUM, 5.0f},
                       {CREATURE_SIZE_LARGE, 10.0f},
                       {CREATURE_SIZE_HUGE, 20.0f},
                       {CREATURE_SIZE_BEHEMOTH, 50.0f} };
}

void Blood::set_litres(const float new_litres)
{
  litres = new_litres;
  calculate_blood_alcohol_content();
}

float Blood::get_litres() const
{
  return litres;
}

void Blood::set_grams_alcohol(const float new_grams_alcohol)
{
  grams_alcohol = new_grams_alcohol;
  calculate_blood_alcohol_content();
}

float Blood::get_grams_alcohol() const
{
  return grams_alcohol;
}

// BAC is defined to be the number of grams of alcohol present in 100mL of blood.
void Blood::calculate_blood_alcohol_content()
{
  float grams_per_millilitre = (grams_alcohol / litres) / 1000;
  blood_alcohol_content = grams_per_millilitre * 100;
}

float Blood::get_blood_alcohol_content() const
{
  return blood_alcohol_content;
}

bool Blood::serialize(ostream& stream) const
{
  Serialize::write_class_id(stream, internal_class_identifier());
  Serialize::write_float(stream, litres);
  Serialize::write_float(stream, grams_alcohol);
  Serialize::write_float(stream, blood_alcohol_content);

  return true;
}

bool Blood::deserialize(istream& stream)
{
  ClassIdentifier throw_away;
  Serialize::read_class_id(stream, throw_away);
  Serialize::read_float(stream, litres);
  Serialize::read_float(stream, grams_alcohol);
  Serialize::read_float(stream, blood_alcohol_content);

  return true;
}

ClassIdentifier Blood::internal_class_identifier() const
{
  return CLASS_ID_BLOOD;
}

#ifdef UNIT_TESTS
#include "unit_tests/Blood_test.cpp"
#endif
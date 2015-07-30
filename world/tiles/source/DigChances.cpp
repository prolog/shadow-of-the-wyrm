#include "DigChances.hpp"
#include "Serialize.hpp"

using namespace std;

DigChances::DigChances()
: pct_chance_undead(0), pct_chance_item(0)
{
}

DigChances::DigChances(const int new_pct_chance_undead, const int new_pct_chance_item)
: pct_chance_undead(new_pct_chance_undead), pct_chance_item(new_pct_chance_item)
{
}

bool DigChances::operator==(const DigChances& dc) const
{
  bool result = true;

  result = result && (pct_chance_undead == dc.pct_chance_undead);
  result = result && (pct_chance_item == dc.pct_chance_item);

  return result;
}

void DigChances::set_pct_chance_undead(const int new_pct_chance_undead)
{
  pct_chance_undead = new_pct_chance_undead;
}

int DigChances::get_pct_chance_undead() const
{
  return pct_chance_undead;
}

void DigChances::set_pct_chance_item(const int new_pct_chance_item)
{
  pct_chance_item = new_pct_chance_item;
}

int DigChances::get_pct_chance_item() const
{
  return pct_chance_item;
}

bool DigChances::serialize(ostream& stream) const
{
  Serialize::write_int(stream, pct_chance_undead);
  Serialize::write_int(stream, pct_chance_item);

  return true;
}

bool DigChances::deserialize(istream& stream)
{
  Serialize::read_int(stream, pct_chance_undead);
  Serialize::read_int(stream, pct_chance_item);

  return true;
}

ClassIdentifier DigChances::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DIG_CHANCES;
}

#ifdef UNIT_TESTS
#include "unit_tests/DigChances_test.cpp"
#endif


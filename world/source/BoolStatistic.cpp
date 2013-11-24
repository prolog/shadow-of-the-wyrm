#include "BoolStatistic.hpp"
#include "Serialize.hpp"

using namespace std;

BoolStatistic::BoolStatistic()
{
  base = true;
  current = true;
}

BoolStatistic::BoolStatistic(const bool new_base_and_current)
{
  base = new_base_and_current;
  current = base;
}

BoolStatistic& BoolStatistic::operator=(const bool& rhs)
{
  base = rhs;
  current = rhs;

  return *this;
}

bool BoolStatistic::operator==(const BoolStatistic& stat) const
{
  bool result = true;

  result = result && (base == stat.base);
  result = result && (current == stat.current);

  return result;
}

void BoolStatistic::set_base(bool new_base)
{
  base = new_base;
}

bool BoolStatistic::get_base() const
{
	return base;
}

void BoolStatistic::set_current(bool new_current)
{
	current = new_current;
}

bool BoolStatistic::get_current() const
{
	return current;
}

bool BoolStatistic::serialize(ostream& stream) const
{
  Serialize::write_bool(stream, base);
  Serialize::write_bool(stream, current);

  return true;
}

bool BoolStatistic::deserialize(istream& stream)
{
  Serialize::read_bool(stream, base);
  Serialize::read_bool(stream, current);

  return false;
}

ClassIdentifier BoolStatistic::internal_class_identifier() const
{
  return CLASS_ID_BOOL_STATISTIC;
}

#ifdef UNIT_TESTS
#include "unit_tests/BoolStatistic_test.cpp"
#endif

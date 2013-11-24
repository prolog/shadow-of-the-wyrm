#include "Statistic.hpp"
#include "Serialize.hpp"

using namespace std;

Statistic::Statistic()
{
  base = 1;
  current = 1;
}

Statistic::Statistic(const int new_base_and_current)
{
  base = new_base_and_current;
  current = base;
}

Statistic& Statistic::operator=(const int& rhs)
{
  base = rhs;
  current = rhs;

  return *this;
}

bool Statistic::operator==(const Statistic& stat) const
{
  bool result = true;

  result = result && (base == stat.base);
  result = result && (current == stat.current);

  return result;
}

/*
 ********************************************************************

 	Get and set the base value of the statistic.  The base value can't
 	go below 0, though the current can.

 ********************************************************************/
void Statistic::set_base(int new_base)
{
  if (new_base > 0)
  {
    base = new_base;
  }
}

int Statistic::get_base() const
{
	return base;
}

/*
 ********************************************************************

 	Get and set the current value of the statistic.

 ********************************************************************/
void Statistic::set_current(int new_current)
{
	current = new_current;
}

int Statistic::get_current() const
{
	return current;
}

bool Statistic::serialize(ostream& stream) const
{
  Serialize::write_int(stream, base);
  Serialize::write_int(stream, current);

  return true;
}

bool Statistic::deserialize(istream& stream)
{
  Serialize::read_int(stream, base);
  Serialize::read_int(stream, current);

  return false;
}

ClassIdentifier Statistic::internal_class_identifier() const
{
  return CLASS_ID_STATISTIC;
}

#ifdef UNIT_TESTS
#include "unit_tests/Statistic_test.cpp"
#endif

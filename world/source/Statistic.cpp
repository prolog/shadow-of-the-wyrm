#include "Statistic.hpp"
#include "Serialize.hpp"

using namespace std;

Statistic::Statistic()
: base(1), current(1), original(1), max(-1), marks(0)
{
}

Statistic::Statistic(const int new_base_and_current)
: base(new_base_and_current), current(new_base_and_current), original(new_base_and_current), max(-1), marks(0)
{
}

Statistic& Statistic::operator=(const int& rhs)
{
  set_base_current(rhs);
  return *this;
}

bool Statistic::operator==(const Statistic& stat) const
{
  bool result = true;

  result = result && (base == stat.base);
  result = result && (current == stat.current);
  result = result && (original == stat.original);
  result = result && (max == stat.max);
  result = result && (marks == stat.marks);

  return result;
}

void Statistic::set_base_current(int new_base_and_current, const SetStatisticFailure ssf)
{
  set_base(new_base_and_current, ssf);
  set_current(new_base_and_current, ssf);
}

// Get and set the base value of the statistic.  The base value can't
// go below 0, though the current can.
void Statistic::set_base(int new_base, const SetStatisticFailure ssf)
{
  if (max == -1 || new_base <= max)
  {
    if (new_base > 0)
    {
      base = new_base;
    }
  }
  else if (new_base > max && ssf == SetStatisticFailure::SET_STATISTIC_FAILURE_TAKE_HIGHEST)
  {
    base = max;
  }
}

int Statistic::get_base() const
{
	return base;
}

// Get and set the current value of the statistic.
void Statistic::set_current(int new_current, const SetStatisticFailure ssf)
{
  if (max == -1 || new_current <= max)
  {
    current = new_current;
  }
  else if (new_current > max && ssf == SetStatisticFailure::SET_STATISTIC_FAILURE_TAKE_HIGHEST)
  {
    current = max;
  }
}

int Statistic::get_current() const
{
	return current;
}

void Statistic::set_original(const int new_original)
{
  original = new_original;
}

int Statistic::get_original() const
{
  return original;
}

void Statistic::set_max(const int new_max)
{
  max = new_max;
}

int Statistic::get_max() const
{
  return max;
}

int Statistic::get_lowest() const
{
  if (current < base)
  {
    return current;
  }
  else
  {
    return base;
  }
}

bool Statistic::get_full() const
{
  return (current == base);
}

int Statistic::get_percent() const
{
  return (100 * current) / base;
}

// True if the number of marks equals the base value.
bool Statistic::get_max_marks() const
{
  return (base == marks.get_value());
}

void Statistic::set_marks(const Marks& new_marks)
{
  marks = new_marks;
}

Marks Statistic::get_marks() const
{
  return marks;
}

Marks& Statistic::get_marks_ref()
{
  return marks;
}

bool Statistic::serialize(ostream& stream) const
{
  Serialize::write_int(stream, base);
  Serialize::write_int(stream, current);
  Serialize::write_int(stream, original);
  Serialize::write_int(stream, max);
  marks.serialize(stream);

  return true;
}

bool Statistic::deserialize(istream& stream)
{
  Serialize::read_int(stream, base);
  Serialize::read_int(stream, current);
  Serialize::read_int(stream, original);
  Serialize::read_int(stream, max);
  marks.deserialize(stream);

  return false;
}

ClassIdentifier Statistic::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_STATISTIC;
}

#ifdef UNIT_TESTS
#include "unit_tests/Statistic_test.cpp"
#endif

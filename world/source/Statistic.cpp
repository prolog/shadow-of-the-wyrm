#include "Statistic.hpp"

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

#ifdef UNIT_TESTS
#include "unit_tests/Statistic_test.cpp"
#endif

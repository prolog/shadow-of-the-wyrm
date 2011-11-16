#include <ctime>
#include <algorithm>
#include "RNG.hpp"

using namespace std;

// Declaration of the random number generator
RNGType RNG::rng;

int RNG::seed = std::time(0);
boost::uniform_int<> RNG::udist = boost::uniform_int<>(0, std::numeric_limits<int>::max());
boost::variate_generator<RNGType, boost::uniform_int<> > RNG::generator(rng, udist);
bool RNG::initialized = false;

RNG::RNG()
{
}

// If the random number generator hasn't been properly initialized by using a timestamp,
// then go ahead and seed it.
bool RNG::initialize_if_necessary()
{
  if (!initialized)
  {
    rng = RNGType(static_cast<unsigned int>(std::time(0)));
    initialized = true;
    return true;
  }

  return false;
}

/*!
 *********************************************************************

	D&D-style dice: roll XdY+Z.

 *********************************************************************/
int RNG::dice
(
  int num_dice
, int num_sides
, int additional_modifier
)
{
  initialize_if_necessary();

  int result = 0;

  for (int num = 0; num < num_dice; num++)
  {
    result += (generator() % num_sides) + 1;
  }

  result += additional_modifier;

  return result;
}

/*
 **********************************************************************

 	Get a number in the range of [min, max], with uniform probability.

 **********************************************************************/
int RNG::range
(
  int first
, int second
, int additional_modifier
)
{
  initialize_if_necessary();

  int minimum = min(first, second);
  int maximum = max(first, second);
  int range = maximum - minimum + 1;
  return (generator() % range) + minimum + additional_modifier;
}

#ifdef UNIT_TESTS
#include "unit_tests/RNG_test.cpp"
#endif

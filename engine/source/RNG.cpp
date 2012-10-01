#include <ctime>
#include <algorithm>
#include "Dice.hpp"
#include "RNG.hpp"

using namespace std;

// Declaration of the random number generator
RNGType RNG::rng;

int RNG::seed = static_cast<int>(std::time(0));
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
    generator.engine().seed(static_cast<uint32_t>(std::time(0)));
    generator.distribution().reset();
    initialized = true;
    return true;
  }

  return false;
}

/*!
 *********************************************************************

	D&D-style dice: roll XdY+Z, either by providing a Dice object, or
	the dice values directly.

 *********************************************************************/
int RNG::dice(const Dice& dice)
{
  int num_dice  = dice.get_num_dice();
  int num_sides = dice.get_dice_sides();
  int modifier  = dice.get_modifier();
  
  return RNG::dice(num_dice, num_sides, modifier);
}

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
int RNG::range(double first, double second)
{
  int i_first = static_cast<int>(first);
  int i_second = static_cast<int>(second);

  return RNG::range(i_first, i_second);
}

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

bool RNG::percent_chance(const int percent_chance)
{
  int val = RNG::range(1, 100);  
  return (val <= percent_chance);
}

#ifdef UNIT_TESTS
#include "unit_tests/RNG_test.cpp"
#endif

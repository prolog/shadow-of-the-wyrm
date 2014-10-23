#include <ctime>
#include <algorithm>
#include "Dice.hpp"
#include "RNG.hpp"

using namespace std;

// Declaration of the random number generator
RNGType RNG::rng;

uint32_t RNG::seed = static_cast<uint32_t>(std::time(0));
boost::uniform_int<> RNG::udist = boost::uniform_int<>(0, std::numeric_limits<int>::max());
boost::variate_generator<RNGType, boost::uniform_int<>> RNG::generator(rng, udist);
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
    seed = static_cast<uint32_t>(std::time(0));
    generator.engine().seed(seed);
    generator.distribution().reset();
    initialized = true;
    return true;
  }

  return false;
}

// Re-initialize.  Useful for saved games where a given seed is known, and needs to be used.
bool RNG::reinitialize()
{
  initialized = false;

  return initialize_if_necessary();
}

// Set a particular seed.  This does not actually reinitialize the RNG - this needs to be done
// separately.
void RNG::set_seed(const uint32_t new_seed)
{
  seed = new_seed;
}

// Get the current seed
uint32_t RNG::get_seed()
{
  return seed;
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

bool RNG::x_in_y_chance(const int x, const int y)
{
  if (x < 0 || y < 0) return false;
  if (x > y) return true;

  int val = RNG::range(1, y);

  return (val <= x);
}

bool RNG::percent_chance(const int percent_chance)
{
  int val = RNG::range(1, 100);  
  return (val <= percent_chance);
}

boost::variate_generator<RNGType, boost::uniform_int<>> RNG::get_generator()
{
  return generator;
}

#ifdef UNIT_TESTS
#include "unit_tests/RNG_test.cpp"
#endif

#include <ctime>
#include <algorithm>
#include "Dice.hpp"
#include "RNG.hpp"

using namespace std;

// Declaration of the random number generator
uint32_t RNG::seed = random_device()();
RNGType RNG::rng = RNGType(seed);
uniform_int_distribution<> RNG::udist = uniform_int_distribution<int>(0, std::numeric_limits<int>::max());

RNG::RNG()
{
}

bool RNG::initialize()
{
  RNGType engine(seed);

  return true;
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

// Random float generation
float RNG::range_f(const float min, const float max)
{
  std::mt19937 gen(rng);
  std::uniform_real_distribution<> dis(min, max);

  return static_cast<float>(dis(rng));
}

// D&D-style dice: roll XdY+Z, either by providing a Dice object, or
// the dice values directly.
int RNG::dice(const Dice& dice)
{
  int num_dice  = dice.get_num_dice();
  int num_sides = dice.get_dice_sides();
  int modifier  = dice.get_modifier();
  
  return RNG::dice(num_dice, num_sides, modifier);
}

int RNG::dice(int num_dice, int num_sides, int additional_modifier)
{
  int result = 0;

  for (int num = 0; num < num_dice; num++)
  {
    result += (udist(rng) % num_sides) + 1;
  }

  result += additional_modifier;

  return result;
}

int RNG::irange(double first, double second)
{
  return range(static_cast<int>(first), static_cast<int>(second));
}

// Get a number in the range of [min, max], with uniform probability.
double RNG::range(double first, double second)
{
  std::mt19937 gen(rng);
  std::uniform_real_distribution<> dis(first, second);

  return dis(rng);
}

int RNG::range(int first, int second, int additional_modifier)
{
  int minimum = min(first, second);
  int maximum = max(first, second);
  int range = maximum - minimum + 1;
  return (udist(rng) % range) + minimum + additional_modifier;
}

bool RNG::x_in_y_chance(const int x, const int y)
{
  if (x <= 0 || y <= 0) return false;
  if (x > y) return true;

  int val = RNG::range(1, y);

  return (val <= x);
}

bool RNG::x_in_y_chance(const pair<int, int>& x_y)
{
  return x_in_y_chance(x_y.first, x_y.second);
}

bool RNG::percent_chance(const int percent_chance)
{
  if (percent_chance <= 0) return false;

  int val = RNG::range(1, 100);
  return (val <= percent_chance);
}

RNGType RNG::get_engine()
{
  return rng;
}

#ifdef UNIT_TESTS
#include "unit_tests/RNG_test.cpp"
#endif

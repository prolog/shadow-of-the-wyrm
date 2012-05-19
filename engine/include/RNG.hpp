#pragma once
#include <boost/random.hpp>

typedef boost::mt19937 RNGType;

class Dice;

class RNG
{
	public:
    RNG();

    static int dice(const Dice& dice);
		static int dice(int num_dice, int num_sides, int additional_modifier = 0);
		static int range(int min, int max, int additional_modifier = 0);
		static bool percent_chance(const int percent_chance);
    static bool initialize_if_necessary();

	protected:
		static RNGType rng;
		static int seed;
		static boost::uniform_int<> udist;
		static boost::variate_generator<RNGType, boost::uniform_int<> > generator;
		static bool initialized;
};

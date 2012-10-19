#pragma once
#include <boost/random.hpp>

typedef boost::mt19937 RNGType;

class Dice;

class RNG
{
	public:
    static int dice(const Dice& dice);
		static int dice(int num_dice, int num_sides, int additional_modifier = 0);
		static int range(int min, int max, int additional_modifier = 0);
    static int range(double min, double max);
		static bool percent_chance(const int percent_chance);
    static bool initialize_if_necessary();
    static bool reinitialize();
    static void set_seed(const uint32_t new_seed);
    static uint32_t get_seed();

	protected:
    RNG();

    static uint32_t seed;
    static RNGType rng;
		static boost::uniform_int<> udist;
		static boost::variate_generator<RNGType, boost::uniform_int<> > generator;
		static bool initialized;
};

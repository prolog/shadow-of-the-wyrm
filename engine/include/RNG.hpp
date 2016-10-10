#pragma once
#include <random>
#include <inttypes.h>

using RNGType = std::mt19937;

class Dice;

class RNG
{
	public:
    static float range_f(float min, float max);
    static int dice(const Dice& dice);
		static int dice(int num_dice, int num_sides, int additional_modifier = 0);
		static int range(int min, int max, int additional_modifier = 0);
    static int range(double min, double max);
		static bool percent_chance(const int percent_chance);
    static bool x_in_y_chance(const int x, const int y);
    static bool x_in_y_chance(const std::pair<int, int>& x_y);
    static bool initialize();
    static void set_seed(const uint32_t new_seed);
    static uint32_t get_seed();
    static RNGType get_engine();

	protected:
    RNG();

    static uint32_t seed;
    static RNGType rng;
		static std::uniform_int_distribution<> udist;
};

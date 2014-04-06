#include "ScoreConstants.hpp"

using namespace std;

// Various constants used to help calculate the player's score when leaving
// the game.

// Did the player win?
const uint ScoreConstants::END_BOSS_BONUS = 500000;

// How much is each level worth?
const uint ScoreConstants::LEVEL_MULTIPLIER = 100;

// How much is each experience point after a certain amount worth?
const vector<pair<uint, double>> ScoreConstants::EXPERIENCE_TIER_MULTIPLIERS{ {1000000, 0.05}, {100000, 0.1}, {10000, 0.2}, {0, 1.0} };


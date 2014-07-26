#include "ConsumableConstants.hpp"

using namespace std;

ConsumableConstants::ConsumableConstants()
{
}

ConsumableConstants::~ConsumableConstants()
{
}

// Used as a key in the item additional property map for consumables to
// indicate that the item is actually a corpse.
const string ConsumableConstants::CORPSE_DESCRIPTION_SID = "CORPSE_DESCRIPTION_SID";

// Food poisoning is more of a sure thing than is getting hit by a 
// poisoned blade.
const int ConsumableConstants::FOOD_POISON_APPLICATION_BONUS = 30;


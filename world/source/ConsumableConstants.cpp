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
const string ConsumableConstants::CORPSE_SHORT_DESCRIPTION_SID = "CORPSE_SHORT_DESCRIPTION_SID";

// Also used as a key in the item additional property map for corpses,
// so that the race of the original creature can be tracked after death.
const string ConsumableConstants::CORPSE_RACE_ID = "CORPSE_RACE_ID";

// Food poisoning is more of a sure thing than is getting hit by a 
// poisoned blade.
const int ConsumableConstants::FOOD_POISON_APPLICATION_BONUS = 30;


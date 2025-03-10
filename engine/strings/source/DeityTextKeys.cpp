#include <boost/algorithm/string/replace.hpp>
#include "DeityTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

// Strings for Prayer
DeityTextKeys::DeityTextKeys()
{
}

DeityTextKeys::~DeityTextKeys()
{
}

string DeityTextKeys::get_prayer_message(const string& deity_sid)
{
  string prayer_message = StringTable::get(DeityTextKeys::PRAYER_INITIAL_MESSAGE);
  boost::replace_first(prayer_message, "%s", StringTable::get(deity_sid));
  
  return prayer_message;
}

string DeityTextKeys::get_deity_change_message(const string& deity_sid)
{
  string change_message = StringTable::get(DeityTextKeys::DEITY_CHANGE_MESSAGE);
  boost::replace_first(change_message, "%s", StringTable::get(deity_sid));

  return change_message;
}

const string DeityTextKeys::ALTAR_SENSE_CROSSALIGNED = "ALTAR_SENSE_CROSSALIGNED";
const string DeityTextKeys::PRAYER_GODLESS           = "PRAYER_GODLESS";
const string DeityTextKeys::PRAYER_INITIAL_MESSAGE   = "PRAYER_INITIAL_MESSAGE";
const string DeityTextKeys::PRAYER_DO_NOTHING        = "PRAYER_DO_NOTHING";
const string DeityTextKeys::PRAYER_FULL_HP           = "PRAYER_FULL_HP";
const string DeityTextKeys::PRAYER_FULL_AP           = "PRAYER_FULL_AP";
const string DeityTextKeys::PRAYER_LEARN_SPELL       = "PRAYER_LEARN_SPELL";
const string DeityTextKeys::PRAYER_SATIATE           = "PRAYER_SATIATE";
const string DeityTextKeys::PRAYER_RESTORE_STATUS    = "PRAYER_RESTORE_STATUS";
const string DeityTextKeys::PRAYER_CROWNING          = "PRAYER_CROWNING";
const string DeityTextKeys::PRAYER_CROWNING_SOLID_GROUND = "PRAYER_CROWNING_SOLID_GROUND";
const string DeityTextKeys::PRAYER_WORLD_MAP         = "PRAYER_WORLD_MAP";
const string DeityTextKeys::PRAYER_PROTECTION        = "PRAYER_PROTECTION";
const string DeityTextKeys::PRAYER_SMITE             = "PRAYER_SMITE";
const string DeityTextKeys::PRAYER_SMITE_DIVINE_LIGHTNING = "PRAYER_SMITE_DIVINE_LIGHTNING";
const string DeityTextKeys::PRAYER_UNCURSE           = "PRAYER_UNCURSE";
const string DeityTextKeys::PRAYER_HALT_BREEDING     = "PRAYER_HALT_BREEDING";
const string DeityTextKeys::PRAYER_COMPANION         = "PRAYER_COMPANION";
const string DeityTextKeys::PRAYER_NO_DEITIES        = "PRAYER_NO_DEITIES";
const string DeityTextKeys::DEITY_CANNOT_PRAY        = "DEITY_CANNOT_PRAY";
const string DeityTextKeys::DEITY_ACTION_DISPLEASED  = "DEITY_ACTION_DISPLEASED"; 
const string DeityTextKeys::DEITY_ACTION_PLEASED     = "DEITY_ACTION_PLEASED";
const string DeityTextKeys::DEITY_FALLEN_CHAMPION    = "DEITY_FALLEN_CHAMPION";
const string DeityTextKeys::DEITY_CHANGE_MESSAGE     = "DEITY_CHANGE_MESSAGE";
const string DeityTextKeys::DEITY_GODLESS            = "DEITY_GODLESS";
const string DeityTextKeys::DEITY_OFFER_GODLESS      = "DEITY_OFFER_GODLESS";
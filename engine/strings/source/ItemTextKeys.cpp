#include <sstream>
#include <iomanip>
#include <boost/algorithm/string/replace.hpp>
#include "ItemTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

ItemTextKeys::ItemTextKeys()
{
}

ItemTextKeys::~ItemTextKeys()
{
}

string ItemTextKeys::get_value(const uint value)
{
  string msg = StringTable::get(ITEM_VALUE);
  boost::replace_first(msg, "%s", to_string(value));

  return msg;
}

string ItemTextKeys::get_nutrition_message(ConsumablePtr consumable)
{
  string msg = StringTable::get(NUTRITION_MESSAGE);
  int turns = 0;

  if (consumable != nullptr)
  {
    turns = consumable->get_nutrition();
  }

  boost::replace_first(msg, "%s", to_string(turns));
  return msg;
}

string ItemTextKeys::get_standard_drinks_message(ConsumablePtr consumable)
{
  string msg = StringTable::get(STANDARD_DRINKS_MESSAGE);
  string drink_cnt = "0";

  if (consumable != nullptr)
  {
    ostringstream ss;
    ss << std::setprecision(1) << consumable->get_standard_drinks();
    drink_cnt = ss.str();
  }

  boost::replace_first(msg, "%s", drink_cnt);
  return msg;
}

string ItemTextKeys::get_number_of_charges_message(WandPtr wand)
{
  string msg = StringTable::get(NUMBER_OF_CHARGES_MESSAGE);
  int charges = 0;

  if (wand != nullptr)
  {
    charges = wand->get_charges().get_current();
  }

  boost::replace_first(msg, "%s", to_string(charges));
  return msg;
}

string ItemTextKeys::get_wearable_protection_message(const int evade, const int soak)
{
  string msg = StringTable::get(WEARABLE_PROTECTION_MESSAGE);

  boost::replace_first(msg, "%s", to_string(evade));
  boost::replace_first(msg, "%s", to_string(soak));

  return msg;
}

string ItemTextKeys::get_speed_modifier_message(const int modifier)
{
  string msg;

  if (modifier >= 0)
  {
    msg = StringTable::get(SPEED_BONUS_MESSAGE);
  }
  else
  {
    msg = StringTable::get(SPEED_PENALTY_MESSAGE);
  }

  boost::replace_first(msg, "%s", to_string(std::abs(modifier)));

  return msg;
}

// Public
const string ItemTextKeys::ITEM_GLOW = "ITEM_GLOW";
const string ItemTextKeys::ITEM_MULTIPLE = "ITEM_MULTIPLE";
const string ItemTextKeys::ITEM_CODEX_NOT_IDENTIFIED = "ITEM_CODEX_NOT_IDENTIFIED";
const string ItemTextKeys::ITEM_CODEX_NO_INFORMATION_FOUND = "ITEM_CODEX_NO_INFORMATION_FOUND";

// Protected
const string ItemTextKeys::ITEM_VALUE = "ITEM_VALUE";
const string ItemTextKeys::NUTRITION_MESSAGE = "NUTRITION_MESSAGE";
const string ItemTextKeys::STANDARD_DRINKS_MESSAGE = "STANDARD_DRINKS_MESSAGE";
const string ItemTextKeys::NUMBER_OF_CHARGES_MESSAGE = "NUMBER_OF_CHARGES_MESSAGE";
const string ItemTextKeys::WEARABLE_PROTECTION_MESSAGE = "WEARABLE_PROTECTION_MESSAGE";
const string ItemTextKeys::SPEED_BONUS_MESSAGE = "SPEED_BONUS_MESSAGE";
const string ItemTextKeys::SPEED_PENALTY_MESSAGE = "SPEED_PENALTY_MESSAGE";

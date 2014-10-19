#include <boost/assert.hpp>
#include "ItemDescriberFactory.hpp"
#include "ReligionConstants.hpp"
#include "SacrificeTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

const string SacrificeTextKeys::SACRIFICE_NO_ALTAR = "SACRIFICE_NO_ALTAR";
const string SacrificeTextKeys::SACRIFICE_NO_ITEMS = "SACRIFICE_NO_ITEMS";
const string SacrificeTextKeys::SACRIFICE_NO_ITEM_SELECTED = "SACRIFICE_NO_ITEM_SELECTED";

string SacrificeTextKeys::get_sacrifice_message(const AlignmentRange align, ItemPtr item, const bool creature_blind)
{
  string message;

  switch (align)
  {
    case ALIGNMENT_RANGE_EVIL:
      message = SACRIFICE_MESSAGE_EVIL;
      break;
    case ALIGNMENT_RANGE_NEUTRAL:
      message = SACRIFICE_MESSAGE_NEUTRAL;
      break;
    case ALIGNMENT_RANGE_GOOD:
      message = SACRIFICE_MESSAGE_GOOD;
      break;
    default:
      BOOST_ASSERT_MSG(false, "Unrecognized alignment for sacrifice message!");
  }

  ItemDescriberPtr id = ItemDescriberFactory::create_item_describer(creature_blind, item);

  message = StringTable::get(message);
  boost::replace_first(message, "%s", id->describe_usage());
  message[0] = toupper(message[0]);

  return message;
}

// Get the piety indicator message that is returned when a creature sacrifices
// an item.
string SacrificeTextKeys::get_piety_message(const int piety)
{
  string message = SACRIFICE_MESSAGE_DISLIKED;

  if (piety > ReligionConstants::PIETY_CROWNING)
  {
    message = SACRIFICE_MESSAGE_CROWNING;
  }
  else if (piety > ReligionConstants::PIETY_TIER_4)
  {
    message = SACRIFICE_MESSAGE_TIER_4;
  }
  else if (piety > ReligionConstants::PIETY_TIER_3)
  {
    message = SACRIFICE_MESSAGE_TIER_3;
  }
  else if (piety > ReligionConstants::PIETY_TIER_2)
  {
    message = SACRIFICE_MESSAGE_TIER_2;
  }
  else if (piety > ReligionConstants::PIETY_TIER_1)
  {
    message = SACRIFICE_MESSAGE_TIER_1;
  }

  return StringTable::get(message);
}

string SacrificeTextKeys::get_altar_conversion_message(const string& deity_name_sid)
{
  string altar_conv_msg = StringTable::get(SacrificeTextKeys::SACRIFICE_MESSAGE_CONVERT_ALTAR);
  string deity_name = StringTable::get(deity_name_sid);

  boost::replace_first(altar_conv_msg, "%s", deity_name);

  return altar_conv_msg;
}

const string SacrificeTextKeys::SACRIFICE_MESSAGE_TIER_1 = "SACRIFICE_MESSAGE_TIER_1";
const string SacrificeTextKeys::SACRIFICE_MESSAGE_TIER_2 = "SACRIFICE_MESSAGE_TIER_2";
const string SacrificeTextKeys::SACRIFICE_MESSAGE_TIER_3 = "SACRIFICE_MESSAGE_TIER_3";
const string SacrificeTextKeys::SACRIFICE_MESSAGE_TIER_4 = "SACRIFICE_MESSAGE_TIER_4";
const string SacrificeTextKeys::SACRIFICE_MESSAGE_CROWNING = "SACRIFICE_MESSAGE_CROWNING";
const string SacrificeTextKeys::SACRIFICE_MESSAGE_DISLIKED = "SACRIFICE_MESSAGE_DISLIKED";

const string SacrificeTextKeys::SACRIFICE_MESSAGE_EVIL = "SACRIFICE_MESSAGE_EVIL";
const string SacrificeTextKeys::SACRIFICE_MESSAGE_GOOD = "SACRIFICE_MESSAGE_GOOD";
const string SacrificeTextKeys::SACRIFICE_MESSAGE_NEUTRAL = "SACRIFICE_MESSAGE_NEUTRAL";
const string SacrificeTextKeys::SACRIFICE_MESSAGE_CONVERT_ALTAR = "SACRIFICE_MESSAGE_CONVERT_ALTAR";

#include <boost/assert.hpp>
#include "ItemDescriberFactory.hpp"
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

const string SacrificeTextKeys::SACRIFICE_MESSAGE_EVIL = "SACRIFICE_MESSAGE_EVIL";
const string SacrificeTextKeys::SACRIFICE_MESSAGE_GOOD = "SACRIFICE_MESSAGE_GOOD";
const string SacrificeTextKeys::SACRIFICE_MESSAGE_NEUTRAL = "SACRIFICE_MESSAGE_NEUTRAL";

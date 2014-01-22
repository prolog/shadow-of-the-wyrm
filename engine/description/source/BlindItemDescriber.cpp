#include "BlindItemDescriber.hpp"
#include "TextKeys.hpp"
#include "StringTable.hpp"

using std::string;

BlindItemDescriber::BlindItemDescriber()
: ItemDescriber(ItemPtr())
{
}

string BlindItemDescriber::describe() const
{
  string item_description = StringTable::get(TextKeys::SOMETHING);
  return item_description;
}

string BlindItemDescriber::describe_usage() const
{
  return describe();
}

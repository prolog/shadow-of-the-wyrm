#include "BlindItemDescriber.hpp"
#include "TextKeys.hpp"
#include "StringTable.hpp"

using std::string;

BlindItemDescriber::BlindItemDescriber()
{
  int x = 1;
}

string BlindItemDescriber::describe() const
{
  string item_description = StringTable::get(TextKeys::SOMETHING);
  return item_description;
}


#include "CreatureDescriber.hpp"

using std::string;

CreatureDescriber::CreatureDescriber(CreaturePtr new_creature)
: creature(new_creature)
{
}

string CreatureDescriber::describe() const
{
  string creature_description;

  if (creature)
  {
    creature_description = StringTable::get(creature->get_description_sid());
  }

  return creature_description;
}

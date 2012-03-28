#include "ReligionFactory.hpp"

using std::string;

ReligionFactory::ReligionFactory()
{
}

Religion ReligionFactory::create_religion(const DeityMap& deities)
{
  Religion religion;
  DeityRelations deity_relations;

  for (DeityMap::const_iterator d_it = deities.begin(); d_it != deities.end(); d_it++)
  {
    DeityStatus new_status;
    string deity_id = d_it->first;

    deity_relations.insert(make_pair(deity_id, new_status));
  }

  religion.set_deity_relations(deity_relations);
  return religion;
}

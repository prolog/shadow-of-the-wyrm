#include "Religion.hpp"

using std::string;

Religion::Religion(const string& new_deity_id)
: deity_id(new_deity_id)
{
}

// If the creature does not worship any deity, the creature is an atheist.
bool Religion::is_atheist() const
{
  return deity_id.empty();
}

// Set/get the information about the deity currently worshipped, using the deity_id
// as the identifer.
void Religion::set_active_deity_id(const string& new_deity_id)
{
  deity_id = new_deity_id;
}

string Religion::get_active_deity_id() const
{
  return deity_id;
}

// Set/get supernatural relations.
void Religion::set_deity_relations(const DeityRelations& new_deity_relations)
{
  deity_relations = new_deity_relations;
}

DeityRelations Religion::get_deity_relations() const
{
  return deity_relations;
}

DeityRelations& Religion::get_deity_relations_ref()
{
  return deity_relations;
}

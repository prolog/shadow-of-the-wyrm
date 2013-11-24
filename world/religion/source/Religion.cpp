#include "Religion.hpp"
#include "Serialize.hpp"

using namespace std;

Religion::Religion(const string& new_deity_id)
: deity_id(new_deity_id)
{
}

bool Religion::operator==(const Religion& r) const
{
  bool result = true;

  result = result && (deity_id == r.deity_id);

  DeityRelations r2 = r.deity_relations;

  result = result  && (deity_relations.size() == r2.size());

  if (result)
  {
    DeityRelations::const_iterator d_it = deity_relations.begin();
    DeityRelations::const_iterator d_it2 = r2.begin();

    while (d_it != deity_relations.end())
    {
      result = result && (d_it->first == d_it2->first);
      result = result && (d_it->second == d_it2->second);

      if (!result) break;
      d_it++;
      d_it2++;
    }
  }

  return result;
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

void Religion::set_deity_status(const std::string& new_deity_id, const DeityStatus& new_deity_status)
{
  deity_relations[new_deity_id] = new_deity_status;
}

DeityStatus Religion::get_deity_status(const std::string& find_deity_id) const
{
  DeityStatus status;
  DeityRelations::const_iterator d_it = deity_relations.find(find_deity_id);
  
  if (d_it != deity_relations.end())
  {
    status = d_it->second;
  }
  
  return status;
}

bool Religion::serialize(ostream& stream) const
{
  Serialize::write_string(stream, deity_id);
  Serialize::write_size_t(stream, deity_relations.size());

  for (const DeityRelations::value_type& relation : deity_relations)
  {
    Serialize::write_string(stream, relation.first);
    relation.second.serialize(stream);
  }

  return true;
}

bool Religion::deserialize(istream& stream)
{
  Serialize::read_string(stream, deity_id);
  size_t deity_relations_size = 0;
  Serialize::read_size_t(stream, deity_relations_size);
  
  deity_relations.clear();

  for (unsigned int i = 0; i < deity_relations_size; i++)
  {
    string deity_id;
    DeityStatus deity_status;

    Serialize::read_string(stream, deity_id);
    deity_status.deserialize(stream);

    deity_relations.insert(make_pair(deity_id, deity_status));
  }

  return true;
}

ClassIdentifier Religion::internal_class_identifier() const
{
  return CLASS_ID_RELIGION;
}

#ifdef UNIT_TESTS
#include "unit_tests/Religion_test.cpp"
#endif


#include "Memberships.hpp"
#include "CreatureFeatures.hpp"
#include "MembershipTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

// Memberships
bool Memberships::operator==(const Memberships& m) const
{
  bool result = true;
  
  result = result && memberships == m.memberships;

  return result;
}

bool Memberships::add_membership(const string& id, const Membership& m)
{
  set<string> exclusions = get_excluded_memberships();

  if (exclusions.find(id) == exclusions.end())
  {
    memberships[id] = m;
    return true;
  }

  return false;
}

bool Memberships::remove_membership(const string& id)
{
  auto m_it = memberships.find(id);

  if (m_it != memberships.end())
  {
    memberships.erase(m_it);
    return true;
  }

  return false;
}

bool Memberships::has_membership(const string& id)
{
  auto m_it = memberships.find(id);

  return (m_it != memberships.end());
}

map<string, Membership> Memberships::get_memberships() const
{
  return memberships;
}

set<string> Memberships::get_excluded_memberships() const
{
  set<string> excl;

  for (auto m_pair : memberships)
  {
    set<string> cur_excl = m_pair.second.get_excluded_memberships();
    excl.insert(cur_excl.begin(), cur_excl.end());
  }

  return excl;
}

ClassIdentifier Memberships::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MEMBERSHIPS;
}

bool Memberships::serialize(ostream& stream) const
{
  Serialize::write_size_t(stream, memberships.size());

  for (const auto& m_pair : memberships)
  {
    Serialize::write_string(stream, m_pair.first);
    m_pair.second.serialize(stream);
  }

  return true;
}

bool Memberships::deserialize(istream& stream)
{
  size_t m_size = 0;
  Serialize::read_size_t(stream, m_size);

  for (size_t i = 0; i < m_size; i++)
  {
    string membership_id;
    Serialize::read_string(stream, membership_id);

    Membership m;
    m.deserialize(stream);

    memberships[membership_id] = m;
  }

  return true;
}

// Individual Membership
Membership::Membership()
{
}

Membership::Membership(const string& new_membership_id, const string& new_desc_sid, const set<string>& new_excluded_memberships)
: membership_id(new_membership_id), description_sid(new_desc_sid), excluded_memberships(new_excluded_memberships)
{
}

bool Membership::operator==(const Membership& m) const
{
  bool result = true;

  result = result && (membership_id == m.membership_id);
  result = result && (description_sid == m.description_sid);
  result = result && (this->excluded_memberships == m.excluded_memberships);

  return result;
}

bool Membership::is_null() const
{
  return membership_id.empty();
}

void Membership::set_membership_id(const string& new_membership_id)
{
  membership_id = new_membership_id;
}

string Membership::get_membership_id() const
{
  return membership_id;
}

void Membership::set_description_sid(const string& new_description_sid)
{
  description_sid = new_description_sid;
}

string Membership::get_description_sid() const
{
  return description_sid;
}

void Membership::add_excluded_membership(const string& excl)
{
  excluded_memberships.insert(excl);
}

void Membership::remove_excluded_membership(const string& excl)
{
  auto e_it = excluded_memberships.find(excl);

  if (e_it != excluded_memberships.end())
  {
    excluded_memberships.erase(e_it);
  }
}

void Membership::set_excluded_memberships(const set<string>& new_excluded_memberships)
{
  excluded_memberships = new_excluded_memberships;
}

set<string> Membership::get_excluded_memberships() const
{
  return excluded_memberships;
}

ClassIdentifier Membership::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MEMBERSHIP;
}

bool Membership::serialize(ostream& stream) const
{
  Serialize::write_string(stream, membership_id);
  Serialize::write_string(stream, description_sid);
  Serialize::write_string_set(stream, excluded_memberships);

  return true;
}

bool Membership::deserialize(istream& stream)
{
  Serialize::read_string(stream, membership_id);
  Serialize::read_string(stream, description_sid);
  Serialize::read_string_set(stream, excluded_memberships);

  return true;
}

Membership MembershipFactory::create_holy_champion()
{
  Membership m(MembershipID::MEMBERSHIP_ID_HOLY_CHAMPION, MembershipTextKeys::MEMBERSHIP_CHAMPION, {});
  return m;
}

Membership MembershipFactory::create_fallen_champion()
{
  Membership m(MembershipID::MEMBERSHIP_ID_FALLEN_CHAMPION, MembershipTextKeys::MEMBERSHIP_FALLEN_CHAMPION, {});
  return m;
}


#ifdef UNIT_TESTS
#include "unit_tests/Memberships_test.cpp"
#endif

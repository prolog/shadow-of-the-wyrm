#include "CharacterCreationDetails.hpp"

using namespace std;

CharacterCreationDetails::CharacterCreationDetails()
: sex(CreatureSex::CREATURE_SEX_MALE)
{
}

CharacterCreationDetails::CharacterCreationDetails(const CreatureSex cs, const string& r_id, const string& c_id, const string& d_id)
: sex(cs), race_id(r_id), class_id(c_id), deity_id(d_id)
{
}

void CharacterCreationDetails::set_sex(const CreatureSex new_sex)
{
  sex = new_sex;
}

CreatureSex CharacterCreationDetails::get_sex() const
{
  return sex;
}

void CharacterCreationDetails::set_race_id(const string& new_race_id)
{
  race_id = new_race_id;
}

string CharacterCreationDetails::get_race_id() const
{
  return race_id;
}

void CharacterCreationDetails::set_class_id(const string& new_class_id)
{
  class_id = new_class_id;
}

string CharacterCreationDetails::get_class_id() const
{
  return class_id;
}

void CharacterCreationDetails::set_deity_id(const string& new_deity_id)
{
  deity_id = new_deity_id;
}

string CharacterCreationDetails::get_deity_id() const
{
  return deity_id;
}

#ifdef UNIT_TESTS
#include "unit_tests/CharacterCreationDetails_test.cpp"
#endif

#include "CharacterCreationDetails.hpp"

using namespace std;

CharacterCreationDetails::CharacterCreationDetails()
: sex(CreatureSex::CREATURE_SEX_NOT_SPECIFIED), hair_colour(HairColour::HAIR_NA), eye_colour(EyeColour::EYE_COLOUR_NA), age(-1)
{
}

CharacterCreationDetails::CharacterCreationDetails(const CreatureSex cs, const HairColour hc, const EyeColour ec, const int cr_age, const string& r_id, const string& c_id, const string& d_id, const StartingLocation& sl)
: sex(cs), hair_colour(hc), eye_colour(ec), age(cr_age), race_id(r_id), class_id(c_id), deity_id(d_id), starting_location(sl)
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

void CharacterCreationDetails::set_hair_colour(const HairColour new_hair_colour)
{
  hair_colour = new_hair_colour;
}

HairColour CharacterCreationDetails::get_hair_colour() const
{
  return hair_colour;
}

void CharacterCreationDetails::set_eye_colour(const EyeColour new_eye_colour)
{
  eye_colour = new_eye_colour;
}

EyeColour CharacterCreationDetails::get_eye_colour() const
{
  return eye_colour;
}

void CharacterCreationDetails::set_age(const int new_age)
{
  age = new_age;
}

int CharacterCreationDetails::get_age() const
{
  return age;
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

void CharacterCreationDetails::set_starting_location(const StartingLocation& new_starting_location)
{
  starting_location = new_starting_location;
}

StartingLocation CharacterCreationDetails::get_starting_location() const
{
  return starting_location;
}

#ifdef UNIT_TESTS
#include "unit_tests/CharacterCreationDetails_test.cpp"
#endif

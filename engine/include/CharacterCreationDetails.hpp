#pragma once
#include <string>
#include "CreatureFeatures.hpp"
#include "StartingLocation.hpp"

// Encapsulates the sex, race, class, and deity selected at the
// new game screen.  These can be user-selected (as when the user selects
// "new game"), or randomly selected, as when the user opts for full or
// partial random creation.
class CharacterCreationDetails
{
  public:
    CharacterCreationDetails();
    CharacterCreationDetails(const CreatureSex cs, const HairColour hc, const EyeColour ec, const int age, const std::string& r_id, const std::string& c_id, const std::string& d_id, const StartingLocation& sl);

    void set_sex(const CreatureSex new_sex);
    CreatureSex get_sex() const;

    void set_hair_colour(const HairColour new_hair_colour);
    HairColour get_hair_colour() const;

    void set_eye_colour(const EyeColour new_eye_colour);
    EyeColour get_eye_colour() const;

    void set_age(const int new_age);
    int get_age() const;

    void set_race_id(const std::string& new_race_id);
    std::string get_race_id() const;

    void set_class_id(const std::string& new_class_id);
    std::string get_class_id() const;

    void set_deity_id(const std::string& new_deity_id);
    std::string get_deity_id() const;

    void set_starting_location(const StartingLocation& new_starting_location);
    StartingLocation get_starting_location() const;

  protected:
    CreatureSex sex;
    HairColour hair_colour;
    EyeColour eye_colour;
    int age;
    std::string race_id;
    std::string class_id;
    std::string deity_id;
    StartingLocation starting_location;
};


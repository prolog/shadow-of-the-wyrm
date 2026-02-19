#pragma once
#include "Class.hpp"
#include "CreatureFeatures.hpp"
#include "Display.hpp"
#include "Race.hpp"

// Class that handles selection for various character attributes (race,
// class, etc). Displays both the regular selection screen as well as 
// an info screen if the player wants to get more info on a particular
// option.
class CharacterSelection
{
  public:
    void select_sex(DisplayPtr display, CreatureSex& sex);
    void select_race(DisplayPtr display, const RaceMap& races, const CreatureSex sex, std::string&, std::string& creature_synopsis);
    void select_class(DisplayPtr display, const ClassMap& classes, const CreatureSex sex, Race* sel_race, string& selected_class_id, string& creature_synopsis);
    void select_hair(DisplayPtr display, const std::string& creature_synopsis, HairColour& hair_colour);
    void select_eyes(DisplayPtr display, const std::string& creature_synopsis, EyeColour& eye_colour);
    void select_age(DisplayPtr display, Race* sel_race, const std::string& creature_synopsis, int& age);
    void select_deity(DisplayPtr display, Race* sel_race, std::string& creature_synopsis, std::string& selected_deity_id);
    void select_starting_location(DisplayPtr display, const CreatureSex sex, Race* sel_race, Class* sel_class, const string& selected_deity_id, std::string& creature_synopsis, StartingLocation& sl);
};

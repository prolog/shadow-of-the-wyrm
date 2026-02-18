#pragma once
#include "CreatureFeatures.hpp"
#include "Display.hpp"

// Class that handles selection for various character attributes (race,
// class, etc). Displays both the regular selection screen as well as 
// an info screen if the player wants to get more info on a particular
// option.
class CharacterSelection
{
  public:
    void select_sex(DisplayPtr display, CreatureSex& sex);
    void select_race(DisplayPtr display, const RaceMap& races, const CreatureSex sex, std::string&, std::string& character_synopsis);
};

#pragma once
#include <string>
#include "CreatureFeatures.hpp"

class ColourTextKeys
{
  public:
    static const std::string COLOUR_BLACK;
    static const std::string COLOUR_BROWN;
    static const std::string COLOUR_BLONDE;
    static const std::string COLOUR_RED;
    static const std::string COLOUR_BLUE;
    static const std::string COLOUR_GREEN;
    static const std::string COLOUR_HAZEL;
    static const std::string COLOUR_GREY;
    static const std::string COLOUR_WHITE;
    
    static std::string get_colour_sid_from_hair_colour(const HairColour hair_colour);
    static std::string get_colour_sid_from_eye_colour(const EyeColour eye_colour);
    
  protected:
    ColourTextKeys();
    ~ColourTextKeys();
};

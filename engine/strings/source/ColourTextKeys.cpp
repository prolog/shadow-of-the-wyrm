#include "ColourTextKeys.hpp"

using namespace std;

// Colours
ColourTextKeys::ColourTextKeys()
{
}

ColourTextKeys::~ColourTextKeys()
{
}

string ColourTextKeys::get_colour_sid_from_hair_colour(const HairColour hair_colour)
{
  string colour_sid;
  
  switch(hair_colour)
  {
    case HairColour::HAIR_COLOUR_BLACK:
      colour_sid = ColourTextKeys::COLOUR_BLACK;
      break;
    case HairColour::HAIR_COLOUR_BROWN:
      colour_sid = ColourTextKeys::COLOUR_BROWN;
      break;
    case HairColour::HAIR_COLOUR_BLONDE:
      colour_sid = ColourTextKeys::COLOUR_BLONDE;
      break;
    case HairColour::HAIR_COLOUR_RED:
      colour_sid = ColourTextKeys::COLOUR_RED;
      break;
    case HairColour::HAIR_COLOUR_GREY:
      colour_sid = ColourTextKeys::COLOUR_GREY;
      break;
    case HairColour::HAIR_COLOUR_WHITE:
      colour_sid = ColourTextKeys::COLOUR_WHITE;
      break;
    default:
      break;
  }
  
  return colour_sid;
}

string ColourTextKeys::get_colour_sid_from_eye_colour(const EyeColour eye_colour)
{
  string colour_sid;
  
  switch(eye_colour)
  {
    case EyeColour::EYE_COLOUR_BROWN:
      colour_sid = COLOUR_BROWN;
      break;
    case EyeColour::EYE_COLOUR_BLUE:
      colour_sid = COLOUR_BLUE;
      break;
    case EyeColour::EYE_COLOUR_GREEN:
      colour_sid = COLOUR_GREEN;
      break;
    case EyeColour::EYE_COLOUR_HAZEL:
      colour_sid = COLOUR_HAZEL;
      break;
    case EyeColour::EYE_COLOUR_GREY:
      colour_sid = COLOUR_GREY;
      break;
    default:
      break;
  }
  
  return colour_sid;
}

const string ColourTextKeys::COLOUR_BLACK = "COLOUR_BLACK";
const string ColourTextKeys::COLOUR_BROWN = "COLOUR_BROWN";
const string ColourTextKeys::COLOUR_BLONDE = "COLOUR_BLONDE";
const string ColourTextKeys::COLOUR_RED = "COLOUR_RED";
const string ColourTextKeys::COLOUR_GREEN = "COLOUR_GREEN";
const string ColourTextKeys::COLOUR_HAZEL = "COLOUR_HAZEL";
const string ColourTextKeys::COLOUR_BLUE = "COLOUR_BLUE";
const string ColourTextKeys::COLOUR_GREY = "COLOUR_GREY";
const string ColourTextKeys::COLOUR_WHITE = "COLOUR_WHITE";

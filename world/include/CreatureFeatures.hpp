#pragma once
enum CreatureSize
{
  CREATURE_SIZE_TINY = 0,
  CREATURE_SIZE_SMALL = 1,
  CREATURE_SIZE_MEDIUM = 2,
  CREATURE_SIZE_LARGE = 3,
  CREATURE_SIZE_HUGE = 4,
  CREATURE_SIZE_BEHEMOTH = 5
};

enum CreatureSex
{
  CREATURE_SEX_MALE = 0,
  CREATURE_SEX_FEMALE = 1
};

enum HairColour
{
  HAIR_COLOUR_BLACK = 0,
  HAIR_COLOUR_BROWN = 1,
  HAIR_COLOUR_BLONDE = 2,
  HAIR_COLOUR_RED = 3,
  HAIR_COLOUR_GREY = 4,
  HAIR_COLOUR_WHITE = 5
};

enum EyeColour
{
  EYE_COLOUR_BROWN = 0,
  EYE_COLOUR_BLUE = 1,
  EYE_COLOUR_GREEN = 2,
  EYE_COLOUR_HAZEL = 3,
  EYE_COLOUR_GREY = 4
};

class CreatureConstants
{
  public:
    static const int DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH;
  
  protected:
    CreatureConstants();
    ~CreatureConstants();
};

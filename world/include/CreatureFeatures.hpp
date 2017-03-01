#pragma once
#include <string>

enum struct CreatureWin
{
  CREATURE_WIN_NO_WIN = 0,
  CREATURE_WIN_REGULAR = 1,
  CREATURE_WIN_EVIL = 2
};

enum struct CreatureSize
{
  CREATURE_SIZE_TINY = 0,
  CREATURE_SIZE_SMALL = 1,
  CREATURE_SIZE_MEDIUM = 2,
  CREATURE_SIZE_LARGE = 3,
  CREATURE_SIZE_HUGE = 4,
  CREATURE_SIZE_BEHEMOTH = 5,
  CREATURE_SIZE_LAST = 6
};

enum struct CreatureSex
{
  CREATURE_SEX_MALE = 0,
  CREATURE_SEX_FEMALE = 1,
  CREATURE_SEX_LAST = 2
};

enum struct HairColour
{
  HAIR_COLOUR_BLACK = 0,
  HAIR_COLOUR_BROWN = 1,
  HAIR_COLOUR_BLONDE = 2,
  HAIR_COLOUR_RED = 3,
  HAIR_COLOUR_GREY = 4,
  HAIR_COLOUR_WHITE = 5
};

enum struct EyeColour
{
  EYE_COLOUR_BROWN = 0,
  EYE_COLOUR_BLUE = 1,
  EYE_COLOUR_GREEN = 2,
  EYE_COLOUR_HAZEL = 3,
  EYE_COLOUR_GREY = 4
};

// This should always mirror the worn location enumeration!
enum struct Handedness
{
  RIGHT_HANDED = 4,
  LEFT_HANDED = 5
};

enum struct BreatheType
{
  BREATHE_TYPE_AIR = 0,
  BREATHE_TYPE_WATER = 1
};

class CreatureConstants
{
  public:
    static const int DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH;
    static const unsigned int MAX_CREATURE_LEVEL;
    static const int MAX_CREATURE_PRIMARY_STATISTIC_VALUE; // str, dex, etc, but not speed, hp, etc.
  protected:
    CreatureConstants();
    ~CreatureConstants();
};

class CreatureEventScripts
{
  public:
    static const std::string CREATURE_EVENT_SCRIPT_DEATH;
    static const std::string CREATURE_EVENT_SCRIPT_ATTACK;
    static const std::string CREATURE_EVENT_SCRIPT_CHAT;
    static const std::string CREATURE_EVENT_SCRIPT_DECISION;
    static const std::string CREATURE_EVENT_SCRIPT_DROP;

  protected:
    CreatureEventScripts();
    ~CreatureEventScripts();
};

class CreatureID
{
  public:
    static const std::string CREATURE_ID_SHOPKEEPER;
    static const std::string CREATURE_ID_FAIRY_SPIRIT;
    static const std::string CREATURE_ID_PLAYER;

  protected:
    CreatureID();
    ~CreatureID();
};

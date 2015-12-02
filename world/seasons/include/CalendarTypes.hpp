#pragma once

enum struct Season
{
  SEASON_SPRING = 0,
  SEASON_SUMMER = 1,
  SEASON_AUTUMN = 2,
  SEASON_WINTER = 3,
  SEASON_LAST = 4
};

enum struct Months
{
  MONTH_1 = 0,
  MONTH_2 = 1,
  MONTH_3 = 2,
  MONTH_4 = 3,
  MONTH_5 = 4,
  MONTH_6 = 5,
  MONTH_7 = 6,
  MONTH_8 = 7,
  MONTH_9 = 8,
  MONTH_10 = 9,
  MONTH_11 = 10,
  MONTH_12 = 11
};

enum struct PhaseOfMoonType
{
  PHASE_OF_MOON_NULL = -1,
  PHASE_OF_MOON_NEW = 0,
  PHASE_OF_MOON_WAXING = 1,
  PHASE_OF_MOON_FULL = 2,
  PHASE_OF_MOON_WANING = 3
};

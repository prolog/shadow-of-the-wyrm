#pragma once

// Describes a creature's champion status with a particular deity -
// a creature can be crowned, uncrowned, or a fallen champion.
enum struct ChampionType
{
  CHAMPION_TYPE_UNCROWNED = 0,
  CHAMPION_TYPE_CROWNED = 1,
  CHAMPION_TYPE_FALLEN = 2
};

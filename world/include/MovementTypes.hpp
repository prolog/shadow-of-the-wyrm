#pragma once

enum struct MovementType
{
  MOVEMENT_TYPE_WALKING = 0, // Also covers swimming
  MOVEMENT_TYPE_FLYING = 1,
  MOVEMENT_TYPE_BOAT = 2
};

// When moving through an occupied tile, there are a number of potential things that can
// happen - attacking, switch places, and squeezing past.
enum struct MovementThroughTileType
{
  MOVEMENT_NONE = 0,
  MOVEMENT_ATTACK = 1,
  MOVEMENT_SWITCH = 2,
  MOVEMENT_SQUEEZE = 3
};


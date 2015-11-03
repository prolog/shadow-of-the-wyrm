#pragma once

enum struct ConductType
{
  CONDUCT_TYPE_FOODLESS = 0,
  CONDUCT_TYPE_VEGETARIAN = 1,
  CONDUCT_TYPE_AGNOSTIC = 2,
  CONDUCT_TYPE_ILLITERATE = 3,
  CONDUCT_TYPE_WEAPONLESS = 4, /* Never hits something with a weapon, rather than not wielding one. */
  CONDUCT_TYPE_NO_GRAVEDIGGING = 5,
  CONDUCT_TYPE_QUESTLESS = 6,
  CONDUCT_SIZE = 7
};


#include "DamageText.hpp"

const float DamageText::PCT_PLAYER_HP_COLOUR_CHANGE = 0.25;

// Damage text is only red if:
// 
// - The creature is the player
// - The creature's current HP is less than 25% of the maximum
Colour DamageText::get_colour(CreaturePtr creature) const
{
  Colour damage_colour = Colour::COLOUR_WHITE;

  if (creature && creature->get_is_player())
  {
    Statistic creature_hp = creature->get_hit_points();
    int threshold = static_cast<int>(creature_hp.get_base() * PCT_PLAYER_HP_COLOUR_CHANGE);

    if (creature_hp.get_current() < threshold)
    {
      damage_colour = Colour::COLOUR_RED;
    }
  }

  return damage_colour;
}

#ifdef UNIT_TESTS
#include "unit_tests/DamageText_test.cpp"
#endif
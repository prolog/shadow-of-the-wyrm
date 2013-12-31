#include "CreatureAlcoholTimer.hpp"

// Check the timer to see if it's time to absorb or metabolize booze.
void CreatureAlcoholTimer::tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature != nullptr)
  {
    uint minutes_for_absorption = alco_calc.calculate_minutes_for_absorption(creature);
    uint minutes_for_metabolization = alco_calc.calculate_minutes_for_metabolization(creature);
    
    if (total_minutes_elapsed % minutes_for_absorption == 0)
    {
      absorb_alcohol(creature);
    }

    if (total_minutes_elapsed % minutes_for_metabolization == 0)
    {
      metabolize_alcohol(creature);
    }
  }
}

// If it's time to absorb alcohol, determine how much unabsorbed alcohol to
// remove from the creature and add to its bloodstream, and modify the
// creature accordingly.
void CreatureAlcoholTimer::absorb_alcohol(CreaturePtr creature)
{
  Blood& blood = creature->get_blood_ref();
  float unabsorbed = creature->get_grams_unabsorbed_alcohol();
  float to_absorb = alco_calc.calculate_grams_to_absorb(creature);

  blood.increment_grams_alcohol(to_absorb);
  creature->decrement_grams_unabsorbed_alcohol(to_absorb);
}

// If it's time to metabolize alcohol, determine how much alcohol should
// be removed from the creature's bloodstream, and modify the creature
// accordingly.
void CreatureAlcoholTimer::metabolize_alcohol(CreaturePtr creature)
{
  Blood& blood = creature->get_blood_ref();
  float absorbed = blood.get_grams_alcohol();
  float to_metabolize = alco_calc.calculate_grams_to_metabolize(creature);
  blood.decrement_grams_alcohol(to_metabolize);
}

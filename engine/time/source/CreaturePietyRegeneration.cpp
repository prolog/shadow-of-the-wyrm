#include "ClassManager.hpp"
#include "CreaturePietyRegeneration.hpp"
#include "ReligionConstants.hpp"
#include "Serialize.hpp"

using namespace std;

int CreaturePietyRegeneration::MINUTES_PER_POINT_OF_PIETY = 10;

void CreaturePietyRegeneration::tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature)
  {
    ClassManager cm;
    
    Religion& religion = creature->get_religion_ref();
    string deity_id = religion.get_active_deity_id();
    DeityStatus deity_status = religion.get_deity_status(deity_id);
    int piety = deity_status.get_piety();
    int new_piety = piety;
    bool crowned = (deity_status.get_champion_type() == ChampionType::CHAMPION_TYPE_CROWNED);
    
    ClassPtr cur_class = cm.get_class(creature->get_class_id());
    
    int piety_regen_bonus = 0;
    
    if (cur_class)
    {
      piety_regen_bonus = cur_class->get_piety_regen_bonus();
    }

    if (piety < 0)
    {
      new_piety = regenerate_piety(piety, piety_regen_bonus, total_minutes_elapsed, crowned);
    }
    else
    {
      if (!crowned)
      {
        new_piety = degenerate_piety(piety, piety_regen_bonus, total_minutes_elapsed);
      }
    }
    
    if (new_piety != piety)
    {
      deity_status.set_piety(new_piety);
      religion.set_deity_status(deity_id, deity_status);
    }
  }
}

// Over time, the Nine like their favoured less - they expect regular sacrifice.  Return the new piety.
int CreaturePietyRegeneration::degenerate_piety(const int piety, const int piety_regen_bonus, const ulonglong minutes_elapsed)
{
  int new_piety = piety;
  
  if (piety >= ReligionConstants::MIN_PIETY_FOR_DEGENERATION)
  {
    int minutes_per_point = std::max(1, MINUTES_PER_POINT_OF_PIETY + piety_regen_bonus);

    if (minutes_elapsed % minutes_per_point == 0)
    {
      new_piety -= ReligionConstants::BASIC_PIETY_INCREMENT;
    }
  }
  
  return new_piety;
}

// Over time, the anger of the Nine lessens.  Return the new piety.
int CreaturePietyRegeneration::regenerate_piety(const int piety, const int piety_regen_bonus, const ulonglong minutes_elapsed, const bool crowned)
{
  int new_piety = piety;
  
  if (piety <= ReligionConstants::MAX_PIETY_FOR_REGENERATION)
  {
    int minutes_per_point = std::max(1, MINUTES_PER_POINT_OF_PIETY - piety_regen_bonus);

    if (minutes_elapsed % minutes_per_point == 0)
    {
      int increment = ReligionConstants::BASIC_PIETY_INCREMENT;
      
      if (crowned)
      {
        increment = ReligionConstants::CROWNED_PIETY_INCREMENT;
      }
      
      new_piety += increment;
    }
  }
  
  return new_piety;
}

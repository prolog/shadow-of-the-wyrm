#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "LevelConstants.hpp"
#include "MessageManager.hpp"
#include "RNG.hpp"

using std::string;

// The experience table, owned as a static member by the manager.
// Ideally, the only C-style array in the entire game.
const uint ExperienceManager::base_experience_table[] = 
{
/* L1-10  */  0,10,25,50,90,150,220,350,500,700,
/* L11-20 */  1000,1400,2000,3000,4500,5700,7500,10000,13500,18000,
/* L21-30 */  21000,28000,35000,50000,75000,105000,150000,200000,260000,340000,
/* L31-40 */  450000,580000,720000,860000,1000000,1400000,1900000,2500000,3500000,5000000,
/* L41-50 */  6850000,9000000,11500000,13000000,15000000,18000000,20000000,2100000,2300000,2500000
};

const int ExperienceManager::base_experience_table_size = 50;

// The experience manager itself
ExperienceManager::ExperienceManager()
{
}

ExperienceManager::~ExperienceManager()
{
}

// Gain experience, gaining a level if necessary
bool ExperienceManager::gain_experience(CreaturePtr creature, const uint experience_value)
{
  bool experience_gained = false;
  
  if (creature)
  {
    creature->set_experience_points(creature->get_experience_points() + experience_value);
    
    if (can_gain_level(creature))
    {
      level_up(creature);
    }
    
    experience_gained = true;
  }
  
  return experience_gained;
}

// Check to see if a creature can gain a level, based on its current level
// and experience totals.
bool ExperienceManager::can_gain_level(CreaturePtr creature)
{
  bool can_gain = false;
  
  if (creature)
  {
    int creature_level = creature->get_level().get_current();
    
    if (creature_level < base_experience_table_size)
    {
      int creature_exp   = creature->get_experience_points();
      
      // If creature_level 1 is, index 1 in table gets the exp needed for
      // level 2, and so on.
      int base_exp_needed = base_experience_table[creature_level];
      
      // Modify by race/class multiplier.
      Game* game = Game::instance();
      
      if (game)
      {
        string race_id = creature->get_race_id();
        string class_id = creature->get_class_id();
        
        float race_multiplier = 1.0f;
        float class_multiplier = 1.0f;
        int actual_exp_required;
        
        if (!race_id.empty())
        {
          RaceMap races = game->get_races_ref();
          RacePtr race = races[race_id];
          race_multiplier = race->get_experience_multiplier();
        }
        
        if (!class_id.empty())
        {
          ClassMap classes = game->get_classes_ref();
          ClassPtr cur_class = classes[class_id];
          class_multiplier = cur_class->get_experience_multiplier();
        }
        
        actual_exp_required = base_exp_needed * race_multiplier * class_multiplier;
        
        if ( creature_exp >= actual_exp_required )
        {
          can_gain = true;
        }
      }
    }    
  }
  
  return can_gain;
}

// Gain a level, increase HP/AP, and do anything else that needs to be done.
void ExperienceManager::level_up(CreaturePtr creature)
{
  MessageManager* manager = MessageManager::instance();
  
  if (creature && manager)
  {
    gain_level(creature);
    gain_hp_and_ap(creature);
    gain_statistics_if_necessary(creature);
    
    if (creature->get_is_player())
    {
      string level_up_message = StringTable::get(TextKeys::GAIN_LEVEL);
      manager->add_new_message(level_up_message);
      manager->send();
      
      // Should monsters' level-ups be broadcast?
    }    
  }
}

void ExperienceManager::gain_level(CreaturePtr creature)
{
  if (creature)
  {
    // If current is less than base (level drain, etc), increase current
    Statistic level   = creature->get_level();
    int current_level = creature->get_level().get_current();
    int base_level    = creature->get_level().get_base();
    
    if (current_level < base_level)
    {
      level.set_current(current_level + 1);
    }    
    // Else, increase both current and base.
    else
    {
      level.set_current(current_level + 1);
      level.set_base(base_level + 1);
    }
    
    creature->set_level(level);
  }
}

void ExperienceManager::gain_hp_and_ap(CreaturePtr creature)
{
  if (creature)
  {
    uint hit_dice = LevelConstants::DEFAULT_HIT_DICE;
    uint ap_dice  = LevelConstants::DEFAULT_AP_DICE;

    string class_id = creature->get_class_id();
    Game* game = Game::instance();
    
    if (game && !class_id.empty())
    {
      ClassMap class_map = game->get_classes_ref();
      ClassPtr current_class = class_map[class_id];
      
      hit_dice = current_class->get_hit_dice();
      ap_dice = current_class->get_ap_dice();
    }

    uint hp_gained = RNG::dice(1, hit_dice, 2);
    uint ap_gained = RNG::dice(1, ap_dice);
    
    Statistic hp = creature->get_hit_points();
    hp.set_base(hp.get_base() + hp_gained);
    hp.set_current(hp.get_current() + hp_gained);
    creature->set_hit_points(hp);
    
    Statistic ap = creature->get_arcana_points();
    ap.set_base(ap.get_base() + ap_gained);
    ap.set_current(ap.get_current() + ap_gained);
    creature->set_arcana_points(ap);
  }
}

void ExperienceManager::gain_statistics_if_necessary(CreaturePtr creature)
{
  if (creature)
  {
    // JCD FIXME
  }
}

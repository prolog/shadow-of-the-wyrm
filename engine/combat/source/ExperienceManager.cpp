#include "ClassManager.hpp"
#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "LevelConstants.hpp"
#include "LevelScript.hpp"
#include "MessageManagerFactory.hpp"
#include "RaceManager.hpp"
#include "RNG.hpp"
#include "SkillsScreen.hpp"
#include "TextKeys.hpp"

using namespace std;

// The experience table, owned as a static member by the manager.
// Ideally, the only C-style array in the entire game.
const uint ExperienceManager::base_experience_table[] = 
{
/* L1-10  */  0,10,25,50,90,150,220,350,500,700,
/* L11-20 */  1000,1400,2000,3000,4500,5700,7500,10000,13500,17000,
/* L21-30 */  21000,28000,35000,50000,75000,105000,150000,200000,260000,340000,
/* L31-40 */  450000,580000,720000,860000,1000000,1400000,1900000,2500000,3500000,5000000,
/* L41-50 */  6850000,9000000,11500000,13000000,15000000,18000000,21000000,24000000,27000000,30000000
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
  int levels_gained = 0;

  if (creature)
  {
    creature->set_experience_points(creature->get_experience_points() + experience_value);
    
    // If the creature has killed something particularly dangerous, the creature might have
    // received sufficient experience to gain more than one level.
    while (can_gain_level(creature))
    {
      level_up(creature);
      levels_gained++;
    }
    
    experience_gained = true;
  }

  // If we've gained at least one level, display the skill advancement screen.
  if (levels_gained > 0)
  {
    // ...
  }
  
  return experience_gained;
}

// Get how far the creature is to the next level, expressed as a percentage.
uint ExperienceManager::get_pct_to_next_level(CreaturePtr creature)
{
  uint tnl_pct = 0;
  
  if (creature)
  {
    Statistic level   = creature->get_level();
    int current_level = level.get_current();
    
    if ((current_level > 0) && (current_level < base_experience_table_size))
    {
      uint current_experience = creature->get_experience_points();
      uint needed_for_current = get_total_experience_needed_for_lvl_idx(creature, current_level-1);
      uint needed_for_next    = get_total_experience_needed_for_lvl_idx(creature, current_level);
      uint normalized_current = current_experience - needed_for_current;
      uint normalized_next    = needed_for_next - needed_for_current;
      float normalized_pct    = (float) normalized_current / (float) normalized_next;
      
      tnl_pct = static_cast<uint>(normalized_pct * 100);
    }
    else
    {
      tnl_pct = 100;
    }
  }
  
  return tnl_pct;
}

uint ExperienceManager::get_total_experience_needed_for_level(CreaturePtr creature, const int level)
{
  return get_total_experience_needed_for_lvl_idx(creature, static_cast<uint>(level - 1));
}

uint ExperienceManager::get_current_experience_needed_for_level(CreaturePtr creature, const uint level)
{
  return get_total_experience_needed_for_lvl_idx(creature, level-1) - creature->get_experience_points();
}

// Get the experience required for a particular level, taking into account any race/class modifiers,
// but not taking into account the amount of xp the creature currently has.
uint ExperienceManager::get_total_experience_needed_for_lvl_idx(CreaturePtr creature, const uint level_idx)
{
  uint exp_needed = 0;
  
  // Check the array bounds to be extra safe!
  if (creature && level_idx >= 0 && level_idx < CreatureConstants::MAX_CREATURE_LEVEL)
  {
    int base_exp_needed = base_experience_table[level_idx];
    
    Game& game = Game::instance();
    
    string race_id = creature->get_race_id();
    string class_id = creature->get_class_id();
      
    float race_multiplier = 1.0f;
    float class_multiplier = 1.0f;

    if (!race_id.empty())
    {
      RaceMap races = game.get_races_ref();
      RacePtr race = races[race_id];
      race_multiplier = race->get_experience_multiplier();
    }
      
    if (!class_id.empty())
    {
      ClassMap classes = game.get_classes_ref();
      ClassPtr cur_class = classes[class_id];
      class_multiplier = cur_class->get_experience_multiplier();
    }
      
    exp_needed = static_cast<int>(base_exp_needed * race_multiplier * class_multiplier);      
  }
  
  return exp_needed;
}

// Check to see if a creature can gain a level, based on its current level
// and experience totals.
bool ExperienceManager::can_gain_level(CreaturePtr creature)
{
  bool can_gain = false;
  
  if (creature)
  {
    int next_lvl_idx = creature->get_level().get_current();
    
    if (next_lvl_idx < base_experience_table_size)
    {
      uint exp_needed = get_total_experience_needed_for_lvl_idx(creature, next_lvl_idx);

      if ( creature->get_experience_points() >= exp_needed )
      {
        can_gain = true;
      }
    }    
  }
  
  return can_gain;
}

// Gain a level, increase HP/AP, and do anything else that needs to be done.
void ExperienceManager::level_up(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  
  if (creature)
  {
    if (creature->get_is_player())
    {
      // Add a paused message so that the player understands that they gain a
      // level.  After this, the skills screen will be shown.
      string level_up_message = StringTable::get(TextKeys::GAIN_LEVEL);
      manager.add_new_message_with_pause(level_up_message, Colour::COLOUR_BOLD_YELLOW);
      creature->get_decision_strategy()->get_confirmation();
      manager.send();
      // Should monsters' level-ups be broadcast?
    }    

    gain_level(creature);
    gain_hp_and_ap(creature);
    gain_statistics(creature);
    run_level_script(creature);
    gain_skills(creature);
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
    Game& game = Game::instance();
    
    if (!class_id.empty())
    {
      ClassMap class_map = game.get_classes_ref();
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

void ExperienceManager::gain_statistics(CreaturePtr creature)
{
  if (creature)
  {
    RaceManager rm;
    RacePtr race = rm.get_race(creature->get_race_id());

    if (race != nullptr)
    {
      int skill_pts = race->get_skill_points();
      creature->increment_skill_points(skill_pts);
    }
  }
}

void ExperienceManager::run_level_script(CreaturePtr creature)
{
  if (creature)
  {
    string race_id  = creature->get_race_id();
    string class_id = creature->get_class_id();
    ClassManager cm;
    RaceManager rm;
    RacePtr racep = rm.get_race(race_id);
    ClassPtr classp = cm.get_class(class_id);

    if (racep && classp)
    {
      LevelScript level_script;
      ScriptEngine& se = Game::instance().get_script_engine_ref();
      se.set_creature(creature);

      vector<string> setup_scripts;
      string race_script = racep->get_level_script();
      string class_script = classp->get_level_script();

      if (!race_script.empty())
      {
        setup_scripts.push_back(racep->get_level_script());
      }

      if (!class_script.empty())
      {
        setup_scripts.push_back(classp->get_level_script());
      }

      try
      {
        level_script.execute(se, setup_scripts, creature);
      }
      catch(...)
      {
      }

      // Ensure that the "local creature" that the scripts can get at is reset
      // appropriately.
      CreaturePtr nullcr;
      se.set_creature(nullcr);
    }
  }
}

void ExperienceManager::gain_skills(CreaturePtr creature)
{
  Game& game = Game::instance();
  SkillCategory category = SkillCategory::SKILL_CATEGORY_GENERAL;

  // JCD FIXME: Later, figure out a reasonable way of assigning new skills
  // to NPCs when they level up.
  if (creature != nullptr && creature->get_is_player())
  {
    int skill_pts = creature->get_skill_points();

    if (skill_pts > 0)
    {
      // Show the Skills screen.
      // Instead of the default skills command processor, use the
      // GainSkillsCommandProcessor.
      SkillsScreen ss(game.get_display(), creature, category, SkillsScreenMode::SKILLS_SCREEN_MODE_IMPROVE_SKILL);
      string display_s = ss.display();
      int input = display_s.at(0);
    }
  }
}
#include <cmath>
#include <boost/make_shared.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "CreatureCalculator.hpp"
#include "CreatureFactory.hpp"
#include "CreatureGenerationConstants.hpp"
#include "Game.hpp"
#include "HostilityManager.hpp"
#include "InitialItemEquipper.hpp"
#include "Log.hpp"
#include "ResistancesCalculator.hpp"
#include "SkillsCalculator.hpp"
#include "HitPointsCalculator.hpp"
#include "ArcanaPointsCalculator.hpp"
#include "ReligionFactory.hpp"
#include "RNG.hpp"
#include "NullKeyboardController.hpp"

using namespace std;

CreaturePtr CreatureFactory::create_by_creature_id
(
  ActionManager& action_manager
, const string& creature_id
)
{
  CreaturePtr creature;
  
  Game& game = Game::instance();
  
  CreatureGenerationValuesMap& cgv_map = game.get_creature_generation_values_ref();
  CreatureMap creature_map = game.get_creatures_ref();
    
  CreatureMap::iterator c_it = creature_map.find(creature_id);
  CreatureGenerationValuesMap::iterator cgv_it = cgv_map.find(creature_id);
    
  if (c_it != creature_map.end() && cgv_it != cgv_map.end())
  {
    // If the current generation amount is equal to the maximum, then
    // we can't generate any more instances of that creature - return
    // the null shared ptr.
    //
    // The default values for current and maximum are 0 and -1,
    // respectively, so by default, there should be no limit to the
    // number of creatures generated for a particular type, so long
    // as a limit has not been specified by the configuration.
    CreatureGenerationValues& cgv  = cgv_it->second;
    if (cgv.is_maximum_reached())
    {
      return creature;
    }

    CreaturePtr creature_template = c_it->second;
      
    Creature creature_instance = *creature_template;
    creature = boost::make_shared<Creature>(creature_instance);
    set_default_resistances(creature);
      
    // Set HP to a randomly generated value in the initial range.
    Dice initial_hp_range = cgv.get_initial_hit_points();
    Statistic hit_points(RNG::dice(initial_hp_range));
    creature->set_hit_points(hit_points);
      
    // Set the exp value to a randomly generated value around the base.
    uint base_experience_value = cgv.get_base_experience_value();
    uint actual_experience_value = RNG::range(ceil(base_experience_value * CreatureGenerationConstants::BASE_EXPERIENCE_LOWER_MULTIPLIER), ceil(base_experience_value * CreatureGenerationConstants::BASE_EXPERIENCE_UPPER_MULTIPLIER));
    creature->set_experience_value(actual_experience_value);
      
    // If the creature is guaranteed to be generated as friendly, then be sure
    // that hostility isn't set.
    if (!cgv.get_friendly())
    {
      // Set the creature hostile to the player, if the player fails a charisma check.
      set_hostility_to_player(creature);
    }
      
    initialize(creature);
    creature->set_original_id(creature_id);

    // Now that the creature has been generated, increment the number of such
    // creatures.
    cgv.incr_current();
  }
    
  InitialItemEquipper iie;
  iie.equip(creature, action_manager);
  iie.add_inventory_items(creature, action_manager);
  
  return creature;
}

CreaturePtr CreatureFactory::create_by_race_and_class
(
  ActionManager& action_manager
, const string& race_id
, const string& class_id
, const string& creature_name
, const CreatureSex creature_sex
, const string& deity_id
)
{
  Creature creature;

  // Set a null controller - this will be overridden later if the creature is a player, or has some
  // special circumstances.
  ControllerPtr null_controller = boost::make_shared<NullKeyboardController>();
  creature.set_is_player(false, null_controller);

  creature.set_name(creature_name);
  creature.set_race_id(race_id);
  creature.set_class_id(class_id);
  creature.set_level(1);
  creature.set_sex(creature_sex);

  Game& game = Game::instance();

  DeityMap deities = game.get_deities_ref();
  RaceMap races = game.get_races_ref();
  ClassMap classes = game.get_classes_ref();

  RacePtr race = races[race_id];
  ClassPtr char_class = classes[class_id];
  DeityPtr deity = deities[deity_id];

  if (race && char_class && deity)
  {
    // Statistics, HP, and AP
    creature = set_initial_statistics(creature, race, char_class, deity);

    // Resistances
    creature = set_initial_resistances(creature, race, char_class);

    // Skills
    creature = set_initial_skills(creature, race, char_class);
      
    // Religion
    Religion religion = ReligionFactory::create_religion(deities);
    religion.set_active_deity_id(deity_id);
    creature.set_religion(religion);
  }

  CreaturePtr creaturep = boost::make_shared<Creature>(creature);

  // Now that everything has been set, set any calculated values.
  if (creaturep)
  {
    // Set additional book-keeping values
    initialize(creaturep);
    
    // Equip the initial set of race/class equipment.
    InitialItemEquipper iie;
    iie.equip(creaturep, action_manager);
    iie.add_inventory_items(creaturep, action_manager);

    // Set calculated statistics
    CreatureCalculator::update_calculated_values(creaturep);
  }

  return creaturep;
}

Creature CreatureFactory::set_initial_statistics(const Creature& current_creature, RacePtr race, ClassPtr char_class, DeityPtr deity)
{
  Creature creature = current_creature;

  StatisticsModifier race_sm = race->get_statistics_modifier();
  StatisticsModifier class_sm = char_class->get_statistics_modifier();
  StatisticsModifier deity_sm = deity->get_initial_statistics_modifier();
  
  Statistic strength     = race->get_starting_strength().get_base()     
                         + class_sm.get_strength_modifier()
                         + deity_sm.get_strength_modifier() 
                         + (RNG::range(0,3));
                         
  Statistic dexterity    = race->get_starting_dexterity().get_base()
                         + class_sm.get_dexterity_modifier()
                         + deity_sm.get_dexterity_modifier() 
                         + (RNG::range(0,3));
                         
  Statistic agility      = race->get_starting_agility().get_base()
                         + class_sm.get_agility_modifier()
                         + deity_sm.get_agility_modifier() 
                         + (RNG::range(0,3));
                         
  Statistic health       = race->get_starting_health().get_base()
                         + class_sm.get_health_modifier()
                         + deity_sm.get_health_modifier()
                         + (RNG::range(0,3));
                         
  Statistic intelligence = race->get_starting_intelligence().get_base()
                         + class_sm.get_intelligence_modifier()
                         + deity_sm.get_intelligence_modifier()
                         + (RNG::range(0,3));
                         
  Statistic willpower    = race->get_starting_willpower().get_base()
                         + class_sm.get_willpower_modifier()
                         + deity_sm.get_willpower_modifier()
                         + (RNG::range(0,3));
                         
  Statistic charisma     = race->get_starting_charisma().get_base()
                         + class_sm.get_charisma_modifier()
                         + deity_sm.get_charisma_modifier()
                         + (RNG::range(0,3));

  Statistic valour       = char_class->get_starting_valour().get_base()
                         + race_sm.get_valour_modifier()
                         + deity_sm.get_valour_modifier(); // no class or random modifiers
                         
  Statistic spirit       = char_class->get_starting_spirit().get_base()
                         + race_sm.get_spirit_modifier()
                         + deity_sm.get_spirit_modifier(); // no class or random modifiers

  Statistic speed = race->get_starting_speed(); // Purely based on race

  creature.set_strength(strength);
  creature.set_dexterity(dexterity);
  creature.set_agility(agility);
  creature.set_health(health);
  creature.set_intelligence(intelligence);
  creature.set_willpower(willpower);
  creature.set_charisma(charisma);

  creature.set_valour(valour);
  creature.set_spirit(spirit);
  creature.set_speed(speed);
  
  creature.set_hair_colour(get_random_hair_colour());
  creature.set_eye_colour(get_random_eye_colour());
  
  AgeInfo age_info = race->get_age_info();
  creature = set_age(creature, age_info);

  CreaturePtr cp = boost::make_shared<Creature>(creature);
  int initial_hp = RNG::dice(3, 3);
  int hp_bonus = HitPointsCalculator::calculate_hit_points_bonus(cp);

  // Calculate HP bonus:
  creature.set_hit_points(initial_hp + hp_bonus);

  // Calculate AP bonus:
  int initial_ap = RNG::dice(2,3);
  int ap_bonus = ArcanaPointsCalculator::calculate_arcana_points_bonus(cp);

  // Calculate AP bonus:
  creature.set_arcana_points(initial_ap + ap_bonus);
  
  return creature;
}

Creature CreatureFactory::set_age(const Creature& current_creature, const AgeInfo& age_info)
{
  Creature creature = current_creature;
  Range<uint> starting_age = age_info.get_starting_age();
  Range<uint> maximum_age = age_info.get_maximum_age();
  
  // Age is a statistic:
  // - Base value is the creature's maximum age (death occurs when the creature gets there)
  // - Current value is the creature's current age
  Statistic age;
  
  age.set_base(RNG::range(maximum_age.get_min(), maximum_age.get_max()));
  age.set_current(RNG::range(starting_age.get_min(), starting_age.get_max()));
  
  creature.set_age(age);
  
  return creature;
}

void CreatureFactory::set_default_resistances(CreaturePtr current_creature)
{
  Resistances resists = ResistancesCalculator::default_resistances();  
  current_creature->set_resistances(resists);
}

Creature CreatureFactory::set_initial_resistances(const Creature& current_creature, RacePtr race, ClassPtr char_class)
{
  Creature creature = current_creature;

  Resistances resists = ResistancesCalculator::calculate_resistances(current_creature, race, char_class);

  creature.set_resistances(resists);

  return creature;
}

Creature CreatureFactory::set_initial_skills(const Creature& current_creature, RacePtr race, ClassPtr char_class)
{
  Creature creature = current_creature;

  // Create a SkillCalculator class!
  Skills skills = SkillsCalculator::calculate_skills(current_creature, race, char_class);

  creature.set_skills(skills);

  return creature;
}

HairColour CreatureFactory::get_random_hair_colour()
{
  int min = HAIR_COLOUR_BLACK;
  int max = HAIR_COLOUR_WHITE;
  
  return static_cast<HairColour>(RNG::range(min, max));
}

EyeColour CreatureFactory::get_random_eye_colour()
{
  int min = EYE_COLOUR_BROWN;
  int max = EYE_COLOUR_GREY;
  
  return static_cast<EyeColour>(RNG::range(min, max));
}

void CreatureFactory::initialize(CreaturePtr creature)
{
  // Generate a unique identifier for this creature.
  boost::uuids::uuid id = boost::uuids::random_generator()();
  std::string id_s = Uuid::to_string(id);
  creature->set_id(id_s);
}

void CreatureFactory::set_hostility_to_player(CreaturePtr npc)
{
  HostilityManager hostility_manager;
  Game& game = Game::instance();
  
  MapPtr map = game.get_current_map();

  // This may be called during the initial game set up, at which point
  // the game will not have a map.
  if (map)
  {
    CreaturePtr player = map->get_creature(PlayerConstants::PLAYER_CREATURE_ID);
    
    if (player && (RNG::percent_chance(100 - player->get_charisma().get_current())))
    {
      hostility_manager.set_hostility_to_player(npc);
    }
  }
  else
  {
    hostility_manager.set_hostility_to_player(npc);
  }
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureFactory_test.cpp"
#endif

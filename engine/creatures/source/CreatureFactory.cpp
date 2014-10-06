#include <cmath>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "CreatureCalculator.hpp"
#include "CreatureFactory.hpp"
#include "CreatureGenerationConstants.hpp"
#include "ExperienceManager.hpp"
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
#include "PlayerConstants.hpp"

using namespace std;

CreatureFactory::CreatureFactory()
: override_hostility_setting(false), create_hostile(false)
{
}

void CreatureFactory::set_hostility_for_creatures(const bool override_host, const bool create_host)
{
  override_hostility_setting = override_host;
  create_hostile = create_host;
}

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
    
  if (!creature_id.empty() && c_it != creature_map.end() && cgv_it != cgv_map.end())
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
    creature = std::make_shared<Creature>(creature_instance);
    DecisionStrategyPtr template_decision_strategy = creature->get_decision_strategy();

    creature = create_by_race_and_class(action_manager,
                                        creature->get_race_id(),
                                        creature->get_class_id(),
                                        creature->get_name(),
                                        creature->get_sex(),
                                        creature->get_religion().get_active_deity_id());

    // Set the template values that would be overridden by creating by race/class.
    // Anything that can be specified under the Creature element in the configuration XML
    // should be added here!
    revert_to_original_configuration_values(creature, creature_instance, template_decision_strategy);
      
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
    if (!cgv.get_friendly() && ((override_hostility_setting && create_hostile) || (!override_hostility_setting)))
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

// After creating by race and class, we have all the original calculated values (str, dex, resists, skills, etc)
// that we want - but we also don't want to overwrite the values for other fields that have been specified in the
// configuration XML.  So this function copies those values back, so that we have a newly generated creature by
// race/class, with all the XML-specified values as well.
void CreatureFactory::revert_to_original_configuration_values(CreaturePtr creature, const Creature& creature_instance, DecisionStrategyPtr template_decision_strategy)
{
    creature->set_colour(creature_instance.get_colour());
    creature->set_symbol(creature_instance.get_symbol());
    creature->set_short_description_sid(creature_instance.get_short_description_sid());
    creature->set_description_sid(creature_instance.get_description_sid());
    creature->set_speech_text_sid(creature_instance.get_speech_text_sid());
    creature->set_breathes(creature_instance.get_breathes());
    creature->set_decision_strategy(template_decision_strategy);
    creature->set_level(creature_instance.get_level());
    creature->set_base_damage(creature_instance.get_base_damage());
    creature->set_base_evade(creature_instance.get_base_evade());
    creature->set_base_soak(creature_instance.get_base_soak());
    creature->set_speed(creature_instance.get_speed());
    creature->set_additional_properties_map(creature_instance.get_additional_properties_map());
    creature->set_event_scripts(creature_instance.get_event_scripts());
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
  CreaturePtr creaturep = std::make_shared<Creature>();

  // Set a null controller - this will be overridden later if the creature is a player, or has some
  // special circumstances.
  ControllerPtr null_controller = std::make_shared<NullKeyboardController>();
  creaturep->set_is_player(false, null_controller);

  creaturep->set_name(creature_name);
  creaturep->set_race_id(race_id);
  creaturep->set_class_id(class_id);
  creaturep->set_level(1);
  creaturep->set_sex(creature_sex);

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
    set_initial_statistics(creaturep, race, char_class, deity);

    // Various race-based flags (boolean statistics)
    if (race->get_corporeal().get_base() == false)
    {
      StatusDuration duration(-1);
      creaturep->set_status(StatusIdentifiers::STATUS_ID_INCORPOREAL, true);
      creaturep->set_status_duration(StatusIdentifiers::STATUS_ID_INCORPOREAL, duration);
    }

    if (race->get_flying().get_base() == true)
    {
      StatusDuration duration(-1);
      creaturep->set_status(StatusIdentifiers::STATUS_ID_FLYING, true);
      creaturep->set_status_duration(StatusIdentifiers::STATUS_ID_FLYING, duration);
    }

    // Resistances
    set_initial_resistances(creaturep, race, char_class);

    // Skills
    set_initial_skills(creaturep, race, char_class);
      
    // Religion & Alignment
    Religion religion = ReligionFactory::create_religion(deities);
    religion.set_active_deity_id(deity_id);
    creaturep->set_religion(religion);

    Alignment alignment;
    alignment.set_alignment(alignment.get_default_alignment_for_range(deity->get_alignment_range()));
    creaturep->set_alignment(alignment);
  }

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

    // Set any abilities, etc., that should be part of level 1.
    ExperienceManager em;
    em.run_level_script(creaturep);
  }

  return creaturep;
}

void CreatureFactory::set_initial_statistics(CreaturePtr creature, RacePtr race, ClassPtr char_class, DeityPtr deity)
{
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

  Statistic speed = race->get_starting_speed(); // Purely based on race

  creature->set_strength(strength);
  creature->set_dexterity(dexterity);
  creature->set_agility(agility);
  creature->set_health(health);
  creature->set_intelligence(intelligence);
  creature->set_willpower(willpower);
  creature->set_charisma(charisma);

  creature->set_speed(speed);
  creature->set_size(race->get_size());
  creature->get_hunger_clock_ref().set_requires_food(race->get_hungerless() == false);
  
  creature->set_hair_colour(get_random_hair_colour());
  creature->set_eye_colour(get_random_eye_colour());
  
  AgeInfo age_info = race->get_age_info();
  set_age(creature, age_info);

  int initial_hp = RNG::dice(3, 3);
  int hp_bonus = HitPointsCalculator::calculate_hit_points_bonus(creature);

  // Calculate HP bonus:
  creature->set_hit_points(initial_hp + hp_bonus);

  // Calculate AP bonus:
  int initial_ap = RNG::dice(2,3);
  int ap_bonus = ArcanaPointsCalculator::calculate_arcana_points_bonus(creature);

  // Calculate AP bonus:
  creature->set_arcana_points(initial_ap + ap_bonus);
}

void CreatureFactory::set_age(CreaturePtr creature, const AgeInfo& age_info)
{
  Range<uint> starting_age = age_info.get_starting_age();
  Range<uint> maximum_age = age_info.get_maximum_age();
  
  // Age is a statistic:
  // - Base value is the creature's maximum age (death occurs when the creature gets there)
  // - Current value is the creature's current age
  Statistic age;
  
  age.set_base(RNG::range(maximum_age.get_min(), maximum_age.get_max()));
  age.set_current(RNG::range(starting_age.get_min(), starting_age.get_max()));
  
  creature->set_age(age);  
}

void CreatureFactory::set_default_resistances(CreaturePtr current_creature)
{
  ResistancesCalculator rc;

  Resistances resists = rc.default_resistances();  
  current_creature->set_resistances(resists);
}

void CreatureFactory::set_initial_resistances(CreaturePtr creature, RacePtr race, ClassPtr char_class)
{
  ResistancesCalculator rc;
  Resistances resists = rc.calculate_resistances(creature, race, char_class);

  creature->set_resistances(resists);
}

void CreatureFactory::set_initial_skills(CreaturePtr creature, RacePtr race, ClassPtr char_class)
{
  // Create a SkillCalculator class!
  Skills skills = SkillsCalculator::calculate_skills(creature, race, char_class);

  creature->set_skills(skills);
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

#include <cmath>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "CreatureCalculator.hpp"
#include "CreatureFactory.hpp"
#include "CreatureGenerationConstants.hpp"
#include "CreatureGenerationOptions.hpp"
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
#include "ModifyStatisticsEffect.hpp"

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
, const string& creature_id_and_options
)
{
  CreaturePtr creature;
  CreatureGenerationOptions cgo;
  cgo.parse(creature_id_and_options);

  string creature_id = cgo.get_id();

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
    CreatureGenerationValues& cgv = cgv_it->second;
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

    // Set AP based on the same.
    Dice initial_ap_range = cgv.get_initial_arcana_points();
    Statistic arcana_points(RNG::dice(initial_ap_range));
    creature->set_arcana_points(arcana_points);

    // If no AP is specified, let AP be 50% of the current HP.
    if (creature->get_arcana_points().get_current() == 0)
    {
      Statistic new_ap(static_cast<int>(hit_points.get_current() * 0.5f));
      creature->set_arcana_points(new_ap);
    }
      
    // Set the exp value to a randomly generated value around the base.
    uint base_experience_value = cgv.get_base_experience_value();
    uint actual_experience_value = RNG::range(ceil(base_experience_value * CreatureGenerationConstants::BASE_EXPERIENCE_LOWER_MULTIPLIER), ceil(base_experience_value * CreatureGenerationConstants::BASE_EXPERIENCE_UPPER_MULTIPLIER));
    creature->set_experience_value(actual_experience_value);

    // Update the statistics based on what's in the initial statistics modifiers.
    set_initial_statistics_modifiers(creature, cgv);

    // Increment the creature's skills based on the skills in the generation
    // values.
    Skills& skills = creature->get_skills();
    skills.increment_skills(cgv.get_skills());
      
    // If the creature is guaranteed to be generated as friendly, then be sure
    // that hostility isn't set.
    if (!cgv.get_friendly() && ((override_hostility_setting && create_hostile) || (!override_hostility_setting)))
    {
      // Set the creature hostile to the player, if the player fails a charisma check.
      set_hostility_to_player(creature);
    }

    map<string, bool> hostility_map = cgo.get_hostility_map();
    auto h_it = hostility_map.find(CreatureID::CREATURE_ID_PLAYER);

    if (h_it != hostility_map.end())
    {
      HostilityManager hm;

      hm.set_hostility_to_player(creature, h_it->second);
    }

    initialize(creature);
    creature->set_original_id(creature_id);

    // Now that the creature has been generated, increment the number of such
    // creatures.
    cgv.incr_current();

    // Add any initial equipment/inventory.
    InitialItemEquipper iie;
    iie.equip(creature, cgv, action_manager);
    iie.add_inventory_items(creature, cgv, action_manager);
  }
      
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
    creature->set_breathes(creature_instance.get_base_breathes());
    creature->set_decision_strategy(template_decision_strategy);
    creature->set_level(creature_instance.get_level());
    creature->set_base_damage(creature_instance.get_base_damage());
    creature->set_base_evade(creature_instance.get_base_evade());
    creature->set_base_soak(creature_instance.get_base_soak());
    creature->set_speed(creature_instance.get_speed());
    creature->set_additional_properties_map(creature_instance.get_additional_properties_map());
    creature->set_spell_knowledge(creature_instance.get_spell_knowledge());
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
    // This'll probably be blank at this point.
    // But for permanent statuses, such as incorporeal/flying, it doesn't
    // really matter.
    string creature_id = creaturep->get_id();

    // Statistics, HP, and AP
    set_initial_statistics(creaturep, race, char_class, deity);

    ModifyStatisticsEffect mse;

    // Various race-based flags (boolean statistics)
    if (race->get_corporeal().get_base() == false)
    {
      Modifier m;
      creaturep->set_status(StatusIdentifiers::STATUS_ID_INCORPOREAL, {StatusIdentifiers::STATUS_ID_INCORPOREAL, true, 1, ""});
      m.set_status(StatusIdentifiers::STATUS_ID_INCORPOREAL, true);
      m.set_permanent(true);
      mse.apply_modifiers(creaturep, m, ModifyStatisticsDuration::MODIFY_STATISTICS_DURATION_PRESET, -1);
    }

    if (race->get_flying().get_base() == true)
    {
      Modifier m;
      creaturep->set_status(StatusIdentifiers::STATUS_ID_FLYING, {StatusIdentifiers::STATUS_ID_FLYING, true, 1, ""});
      m.set_status(StatusIdentifiers::STATUS_ID_FLYING, true);
      mse.apply_modifiers(creaturep, m, ModifyStatisticsDuration::MODIFY_STATISTICS_DURATION_PRESET, -1);
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

    // Create initial eq based on class and creature defaults.
    create_initial_equipment_and_inventory(creaturep, action_manager);
    
    // Set calculated statistics
    CreatureCalculator::update_calculated_values(creaturep);

    // Set any abilities, etc., that should be part of level 1.
    ExperienceManager em;
    em.run_level_script(creaturep);
  }

  return creaturep;
}

void CreatureFactory::create_initial_equipment_and_inventory(CreaturePtr creaturep, ActionManager& action_manager)
{
  Game& game = Game::instance();
  const CreatureGenerationValuesMap& cgv_map = game.get_creature_generation_values_ref();
  CreatureGenerationValues cgv;

  auto cgv_it = cgv_map.find(creaturep->get_original_id());

  if (cgv_it != cgv_map.end())
  {
    cgv = cgv_it->second;
  }

  // Equip the initial set of race/class equipment.
  InitialItemEquipper iie;
  iie.equip(creaturep, cgv, action_manager);
  iie.add_inventory_items(creaturep, cgv, action_manager);
}

void CreatureFactory::set_initial_statistics(CreaturePtr creature, RacePtr race, ClassPtr char_class, DeityPtr deity)
{
  Modifier race_m = race->get_modifier();
  Modifier class_m = char_class->get_modifier();
  Modifier deity_m = deity->get_initial_modifier();
  
  Statistic strength     = race->get_starting_strength().get_base()     
                         + class_m.get_strength_modifier()
                         + deity_m.get_strength_modifier() 
                         + (RNG::range(0,3));
                         
  Statistic dexterity    = race->get_starting_dexterity().get_base()
                         + class_m.get_dexterity_modifier()
                         + deity_m.get_dexterity_modifier() 
                         + (RNG::range(0,3));
                         
  Statistic agility      = race->get_starting_agility().get_base()
                         + class_m.get_agility_modifier()
                         + deity_m.get_agility_modifier() 
                         + (RNG::range(0,3));
                         
  Statistic health       = race->get_starting_health().get_base()
                         + class_m.get_health_modifier()
                         + deity_m.get_health_modifier()
                         + (RNG::range(0,3));
                         
  Statistic intelligence = race->get_starting_intelligence().get_base()
                         + class_m.get_intelligence_modifier()
                         + deity_m.get_intelligence_modifier()
                         + (RNG::range(0,3));
                         
  Statistic willpower    = race->get_starting_willpower().get_base()
                         + class_m.get_willpower_modifier()
                         + deity_m.get_willpower_modifier()
                         + (RNG::range(0,3));
                         
  Statistic charisma     = race->get_starting_charisma().get_base()
                         + class_m.get_charisma_modifier()
                         + deity_m.get_charisma_modifier()
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

// Primary stats can be modified for creatures not created via race/class
void CreatureFactory::set_initial_statistics_modifiers(CreaturePtr creature, const CreatureGenerationValues& cgv)
{
  if (creature != nullptr)
  {
    Modifier stat_mod = cgv.get_modifier();

    Statistic& strength = creature->get_strength_ref();
    strength.set_base_current(strength.get_base() + stat_mod.get_strength_modifier());

    Statistic& dexterity = creature->get_dexterity_ref();
    dexterity.set_base_current(dexterity.get_base() + stat_mod.get_dexterity_modifier());

    Statistic& agility = creature->get_agility_ref();
    agility.set_base_current(agility.get_base() + stat_mod.get_agility_modifier());

    Statistic& health = creature->get_health_ref();
    health.set_base_current(health.get_base() + stat_mod.get_health_modifier());

    Statistic& intelligence = creature->get_intelligence_ref();
    intelligence.set_base_current(intelligence.get_base() + stat_mod.get_intelligence_modifier());

    Statistic& willpower = creature->get_willpower_ref();
    willpower.set_base_current(willpower.get_base() + stat_mod.get_willpower_modifier());

    Statistic& charisma = creature->get_charisma_ref();
    charisma.set_base_current(charisma.get_base() + stat_mod.get_charisma_modifier());
  }
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
  int min = static_cast<int>(HairColour::HAIR_COLOUR_BLACK);
  int max = static_cast<int>(HairColour::HAIR_COLOUR_WHITE);
  
  return static_cast<HairColour>(RNG::range(min, max));
}

EyeColour CreatureFactory::get_random_eye_colour()
{
  int min = static_cast<int>(EyeColour::EYE_COLOUR_BROWN);
  int max = static_cast<int>(EyeColour::EYE_COLOUR_GREY);
  
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
    CreaturePtr player = map->get_creature(CreatureID::CREATURE_ID_PLAYER);
    
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

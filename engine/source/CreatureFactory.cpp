#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "CreatureFactory.hpp"
#include "Game.hpp"
#include "ResistancesCalculator.hpp"
#include "SkillsCalculator.hpp"
#include "HitPointsCalculator.hpp"
#include "ArcanaPointsCalculator.hpp"
#include "RNG.hpp"

using namespace std;

CreaturePtr CreatureFactory::create_by_creature_id(const string& creature_id)
{
  CreaturePtr totally_bogus_default_creature_null;

  // Creature IDs aren't supported yet.

  return totally_bogus_default_creature_null;
}

CreaturePtr CreatureFactory::create_by_race_and_class(const string& race_id, const string& class_id, const string& creature_name)
{
  Creature creature;

  // Generate a unique identifier for this creature.
  boost::uuids::uuid id = boost::uuids::random_generator()();
  creature.set_id(id);

  creature.set_name(creature_name);
  creature.set_race_id(race_id);
  creature.set_class_id(class_id);
  creature.set_level(1);

  Game* game = Game::instance();

  if (game)
  {
    // Real work goes here.
    RaceMap races = game->get_races_ref();
    ClassMap classes = game->get_classes_ref();

    RacePtr race = races[race_id];
    ClassPtr char_class = classes[class_id];

    if (race && char_class)
    {
      // Statistics, HP, and AP
      creature = set_initial_statistics(creature, race, char_class);

      // Resistances
      creature = set_initial_resistances(creature, race, char_class);

      // Skills
      creature = set_initial_skills(creature, race, char_class);
    }
  }

  CreaturePtr creaturep = CreaturePtr(new Creature(creature));
  return creaturep;
}

Creature CreatureFactory::set_initial_statistics(Creature current_creature, RacePtr race, ClassPtr char_class)
{
  Creature creature = current_creature;

  Statistic strength     = race->get_starting_strength().get_base()     + char_class->get_strength_modifier()     + (RNG::range(1,4) - 2);
  Statistic dexterity    = race->get_starting_dexterity().get_base()    + char_class->get_dexterity_modifier()    + (RNG::range(1,4) - 2);
  Statistic agility      = race->get_starting_agility().get_base()      + char_class->get_agility_modifier()      + (RNG::range(1,4) - 2);
  Statistic health       = race->get_starting_health().get_base()       + char_class->get_health_modifier()       + (RNG::range(1,4) - 2);
  Statistic intelligence = race->get_starting_intelligence().get_base() + char_class->get_intelligence_modifier() + (RNG::range(1,4) - 2);
  Statistic willpower    = race->get_starting_willpower().get_base()    + char_class->get_willpower_modifier()    + (RNG::range(1,4) - 2);
  Statistic charisma     = race->get_starting_charisma().get_base()     + char_class->get_charisma_modifier()     + (RNG::range(1,4) - 2);

  Statistic valour = char_class->get_starting_valour().get_base() + race->get_valour_modifier();
  Statistic spirit = char_class->get_starting_spirit().get_base() + race->get_spirit_modifier();
  Statistic speed = race->get_starting_speed();

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
  creature.set_piety(0); // FIXME

  CreaturePtr cp = CreaturePtr(new Creature(creature));
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

Creature CreatureFactory::set_initial_resistances(Creature current_creature, RacePtr race, ClassPtr char_class)
{
  Creature creature = current_creature;

  Resistances resists = ResistancesCalculator::calculate_resistances(current_creature, race, char_class);

  creature.set_resistances(resists);

  return creature;
}

Creature CreatureFactory::set_initial_skills(Creature current_creature, RacePtr race, ClassPtr char_class)
{
  Creature creature = current_creature;

  // Create a SkillCalculator class!
  Skills skills = SkillsCalculator::calculate_skills(current_creature, race, char_class);

  creature.set_skills(skills);

  return creature;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureFactory_test.cpp"
#endif

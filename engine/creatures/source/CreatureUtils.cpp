#include "Conversion.hpp"
#include "CreatureUtils.hpp"
#include "Game.hpp"

using namespace std;

CreatureUtils::CreatureUtils()
{
}

CreatureUtils::~CreatureUtils()
{
}

string CreatureUtils::get_race_class_synopsis(CreaturePtr c)
{
  string synopsis;
  Game& game = Game::instance();

  string race_id = c->get_race_id();
  string class_id = c->get_class_id();
  RaceMap races = game.get_races_ref();
  ClassMap classes = game.get_classes_ref();

  RacePtr race = races[race_id];
  ClassPtr current_class = classes[class_id];

  if (race && current_class)
  {
    synopsis = StringTable::get(race->get_race_abbreviation_sid()) + StringTable::get(current_class->get_class_abbreviation_sid());
    synopsis = String::add_trailing_spaces(synopsis, 5);
  }

  synopsis = String::add_trailing_spaces(synopsis, 5);

  return synopsis;
}


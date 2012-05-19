#include "Creature.hpp"
#include "PlayerDecisionStrategy.hpp"

using namespace std;

// Set a reasonable set of default values for simple types, which are helpfully initialized to bullshit memory.
// Why did I write this in C++?
Creature::Creature()
: is_player(false)
, sex(CREATURE_SEX_MALE)
, size(CREATURE_SIZE_MEDIUM)
, eye_colour(EYE_COLOUR_BROWN)
, hair_colour(HAIR_COLOUR_BLACK)
, ivory_pieces(0)
, symbol('?')
, colour(COLOUR_WHITE)
// Everything else is a string, Statistic, etc, and is not a primitive type.  These'll have their own constructors.
// Religion defaults to atheist.
{
  set_evade(0);
  set_soak (0);
  
  Damage dam(1, 2, 0, DAMAGE_TYPE_POUND);
  set_base_damage(dam);
}

void Creature::set_id(const string& new_id)
{
  id = new_id;
}

string Creature::get_id() const
{
  return id;
}

void Creature::set_is_player(const bool player, ControllerPtr controller)
{
  is_player = player;
  decision_strategy.reset();

  if (player)
  {
    // Players always use the PlayerDecisionStrategy class so that keyboard input
    // can be used.
    decision_strategy = DecisionStrategyPtr(new PlayerDecisionStrategy(controller));

    // Players are always @s.
    set_symbol('@');
  }
}

bool Creature::get_is_player() const
{
  return is_player;
}

void Creature::set_name(const string& new_name)
{
  name = new_name;
}

string Creature::get_name() const
{
  return name;
}

bool Creature::has_name() const
{
  return (!name.empty());
}

void Creature::set_short_description_sid(const string& new_short_description_sid)
{
  short_description_sid = new_short_description_sid;
}

string Creature::get_short_description_sid() const
{
  return short_description_sid;
}

void Creature::set_description_sid(const string& new_description_sid)
{
  description_sid = new_description_sid;
}

string Creature::get_description_sid() const
{
  return description_sid;
}

void Creature::set_sex(const CreatureSex new_sex)
{
  sex = new_sex;
}

CreatureSex Creature::get_sex() const
{
  return sex;
}

void Creature::set_age(const Statistic& new_age)
{
  age = new_age;
}

Statistic Creature::get_age() const
{
  return age;
}

void Creature::set_size(const CreatureSize& new_size)
{
  size = new_size;
}

CreatureSize Creature::get_size() const
{
  return size;
}

void Creature::set_eye_colour(const EyeColour new_eye_colour)
{
  eye_colour = new_eye_colour;
}

EyeColour Creature::get_eye_colour() const
{
  return eye_colour;
}

void Creature::set_hair_colour(const HairColour new_hair_colour)
{
  hair_colour = new_hair_colour;
}

HairColour Creature::get_hair_colour() const
{
  return hair_colour;
}

void Creature::set_race_id(const string& new_race_id)
{
  race_id = new_race_id;
}

string Creature::get_race_id() const
{
  return race_id;
}

void Creature::set_class_id(const string& new_class_id)
{
  class_id = new_class_id;
}

string Creature::get_class_id() const
{
  return class_id;
}

void Creature::set_strength(const Statistic& new_strength)
{
  strength = new_strength;
}

Statistic Creature::get_strength() const
{
  return strength;
}

void Creature::set_dexterity(const Statistic& new_dexterity)
{
  dexterity = new_dexterity;
}

Statistic Creature::get_dexterity() const
{
  return dexterity;
}

void Creature::set_agility(const Statistic& new_agility)
{
  agility = new_agility;
}

Statistic Creature::get_agility() const
{
  return agility;
}

void Creature::set_health(const Statistic& new_health)
{
  health = new_health;
}

Statistic Creature::get_health() const
{
  return health;
}

void Creature::set_intelligence(const Statistic& new_intelligence)
{
  intelligence = new_intelligence;
}

Statistic Creature::get_intelligence() const
{
  return intelligence;
}

void Creature::set_willpower(const Statistic& new_willpower)
{
  willpower = new_willpower;
}

Statistic Creature::get_willpower() const
{
  return willpower;
}

void Creature::set_charisma(const Statistic& new_charisma)
{
  charisma = new_charisma;
}

Statistic Creature::get_charisma() const
{
  return charisma;
}

void Creature::set_valour(const Statistic& new_valour)
{
  valour = new_valour;
}

Statistic Creature::get_valour() const
{
  return valour;
}

void Creature::set_spirit(const Statistic& new_spirit)
{
  spirit = new_spirit;
}

Statistic Creature::get_spirit() const
{
  return spirit;
}

void Creature::set_piety(const Statistic& new_piety)
{
  piety = new_piety;
}

Statistic Creature::get_piety() const
{
  return piety;
}

void Creature::set_speed(const Statistic& new_speed)
{
  speed = new_speed;
}

Statistic Creature::get_speed() const
{
  return speed;
}

void Creature::set_resistance_value(const DamageType damage_type, double value)
{
  resistances.set_resistance_value(damage_type, value);
}

void Creature::set_resistances(const Resistances& new_resistances)
{
  resistances = new_resistances;
}

Resistances& Creature::get_resistances()
{
  return resistances;
}

void Creature::set_skills(const Skills& new_skills)
{
  skills = new_skills;
}

Skills& Creature::get_skills()
{
  return skills;
}

void Creature::set_base_damage(const Damage& new_base_damage)
{
  damage = new_base_damage;
}

Damage Creature::get_base_damage() const
{
  return damage;
}

Equipment& Creature::get_equipment()
{
  return equipment;
}

Inventory& Creature::get_inventory()
{
  return inventory;
}

void Creature::set_ivory_pieces(const uint new_ivory_pieces)
{
  ivory_pieces = new_ivory_pieces;
}

uint Creature::get_ivory_pieces() const
{
  return ivory_pieces;
}

void Creature::set_hit_points(const Statistic& new_hit_points)
{
  hit_points = new_hit_points;
}

void Creature::increment_hit_points(const int amount)
{
  hit_points.set_current(hit_points.get_current() + amount);
}

void Creature::decrement_hit_points(const int amount)
{
  hit_points.set_current(hit_points.get_current() - amount);
}

Statistic Creature::get_hit_points() const
{
  return hit_points;
}

void Creature::set_arcana_points(const Statistic& new_arcana_points)
{
  arcana_points = new_arcana_points;
}

void Creature::increment_arcana_points(const int amount)
{
  arcana_points.set_current(arcana_points.get_current() + amount);
}

void Creature::decrement_arcana_points(const int amount)
{
  arcana_points.set_current(arcana_points.get_current() - amount);
}

Statistic Creature::get_arcana_points() const
{
  return arcana_points;
}

void Creature::set_evade(const Statistic& new_evade)
{
  evade = new_evade;
}

Statistic Creature::get_evade() const
{
  return evade;
}

void Creature::set_soak(const Statistic& new_soak)
{
  soak = new_soak;
}

Statistic Creature::get_soak() const
{
  return soak;
}

void Creature::set_symbol(const uchar new_symbol)
{
  symbol = new_symbol;
}

uchar Creature::get_symbol() const
{
  return symbol;
}

void Creature::set_colour(const Colour new_colour)
{
  colour = new_colour;
}

Colour Creature::get_colour() const
{
  return colour;
}

void Creature::set_level(const Statistic& new_level)
{
  level = new_level;
}

Statistic Creature::get_level() const
{
  return level;
}

void Creature::set_decision_strategy(const DecisionStrategyPtr strategy)
{
  decision_strategy = strategy;
}

DecisionStrategyPtr Creature::get_decision_strategy() const
{
  return decision_strategy;
}

void Creature::set_religion(const Religion& new_religion)
{
  religion = new_religion;
}

Religion Creature::get_religion() const
{
  return religion;
}

Religion& Creature::get_religion_ref()
{
  return religion;
}

#ifdef UNIT_TESTS
#include "unit_tests/Creature_test.cpp"
#endif

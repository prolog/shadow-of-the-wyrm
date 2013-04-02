#include <limits>
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "Creature.hpp"
#include "DecisionStrategyFactory.hpp"
#include "PlayerDecisionStrategy.hpp"
#include "Serialize.hpp"

using namespace std;

// Set a reasonable set of default values for simple types, which are helpfully initialized to bullshit memory.
// Why did I write this in C++?
Creature::Creature()
: is_player(false)
, sex(CREATURE_SEX_MALE)
, size(CREATURE_SIZE_MEDIUM)
, eye_colour(EYE_COLOUR_BROWN)
, hair_colour(HAIR_COLOUR_BLACK)
, handedness(RIGHT_HANDED)
, symbol('?')
, colour(COLOUR_WHITE)
, experience_value(0)
, experience_points(0)
, turns(0)
// Everything else is a string, Statistic, etc, and is not a primitive type.  These'll have their own constructors.
// Religion defaults to atheist.
{
  set_base_evade(0);
  set_base_soak(0);
  set_evade(0);
  set_soak (0);
  
  // Base speed is 50.  This needs to be set or slimes get 25 actions to your 1 (23 or 24 if you're quick!).
  set_speed(50);
  
  Damage dam(1, 2, 0, DAMAGE_TYPE_POUND);
  set_base_damage(dam);
}

// Need to define these because of the ControllerPtr and DecisionStrategyPtr
// defined in the class - without it, a shared_ptr to a decision strategy 
// doesn't always do what you expect!
Creature::Creature(const Creature& cr)
{
  id = cr.id;
  original_id = cr.original_id;
  is_player = cr.is_player;
  name = cr.name;
  sex = cr.sex;
  age = cr.age;
  size = cr.size;
  eye_colour = cr.eye_colour;
  hair_colour = cr.hair_colour;
  handedness = cr.handedness;
  short_description_sid = cr.short_description_sid;
  description_sid = cr.description_sid;
  race_id = cr.race_id;
  class_id = cr.class_id;
  strength = cr.strength;
  dexterity = cr.dexterity;
  agility = cr.agility;
  health = cr.health;
  intelligence = cr.intelligence;
  willpower = cr.willpower;
  charisma = cr.charisma;
  valour = cr.valour;
  spirit = cr.spirit;
  speed = cr.speed;
  damage = cr.damage;
  equipment = cr.equipment;
  inventory = cr.inventory;
  resistances = cr.resistances;
  skills = cr.skills;
  movement_accumulation = cr.movement_accumulation;
  hit_points = cr.hit_points;
  arcana_points = cr.arcana_points;
  base_evade = cr.base_evade;
  base_soak = cr.base_soak;
  evade = cr.evade;
  soak = cr.soak;
  symbol = cr.symbol;
  colour = cr.colour;
  level = cr.level;
  
  if (cr.decision_strategy)
  {
    // Without the copy constuctor, the raw pointer was being shared between creature instances,
    // and the threat map for supposedly peaceful creatures contained the player, making the creature hostile!
    decision_strategy = boost::shared_ptr<DecisionStrategy>(cr.decision_strategy->copy());
  }
  
  religion = cr.religion;
  experience_value = cr.experience_value;
  experience_points = cr.experience_points;
  turns = cr.turns;
  targets = cr.targets;  
  hunger = cr.hunger;
  event_functions = cr.event_functions;
  additional_properties = cr.additional_properties;
  mortuary = cr.mortuary;
  spell_knowledge = cr.spell_knowledge;
}

Creature& Creature::operator=(const Creature& cr)
{
  if (this != &cr)
  {
    Creature temp(cr);
    temp.swap(*this);
  }

  return *this;
}

bool Creature::operator==(const Creature& cr)
{
  bool result = true;

  result = result && (id == cr.id);
  result = result && (original_id == cr.original_id);
  result = result && (is_player == cr.is_player);
  result = result && (name == cr.name);
  result = result && (sex == cr.sex);
  result = result && (age == cr.age);
  result = result && (size == cr.size);
  result = result && (eye_colour == cr.eye_colour);
  result = result && (hair_colour == cr.hair_colour);
  result = result && (handedness == cr.handedness);
  result = result && (short_description_sid == cr.short_description_sid);
  result = result && (description_sid == cr.description_sid);
  result = result && (race_id == cr.race_id);
  result = result && (class_id == cr.class_id);
  result = result && (strength == cr.strength);
  result = result && (dexterity == cr.dexterity);
  result = result && (agility == cr.agility);
  result = result && (health == cr.health);
  result = result && (intelligence == cr.intelligence);
  result = result && (willpower == cr.willpower);
  result = result && (charisma == cr.charisma);
  result = result && (valour == cr.valour);
  result = result && (spirit == cr.spirit);
  result = result && (speed == cr.speed);
  result = result && (damage == cr.damage);
  result = result && (equipment == cr.equipment);
  result = result && (inventory == cr.inventory);
  result = result && (resistances == cr.resistances);
  result = result && (skills == cr.skills);
  result = result && (movement_accumulation == cr.movement_accumulation);
  result = result && (hit_points == cr.hit_points);
  result = result && (arcana_points == cr.arcana_points);
  result = result && (base_evade == cr.base_evade);
  result = result && (evade == cr.evade);
  result = result && (base_soak == cr.base_soak);
  result = result && (soak == cr.soak);
  result = result && (symbol == cr.symbol);
  result = result && (colour == cr.colour);
  result = result && (level == cr.level);
  result = result && ((decision_strategy && cr.decision_strategy) || (!decision_strategy && !cr.decision_strategy));

  if (result && decision_strategy)
  {
    result = result && (*decision_strategy == *cr.decision_strategy);
  }

  result = result && (religion == cr.religion);
  result = result && (experience_value == cr.experience_value);
  result = result && (experience_points == cr.experience_points);
  result = result && (turns == cr.turns);
  result = result && (targets == cr.targets);
  result = result && (hunger == cr.hunger);
  result = result && (event_functions == cr.event_functions);
  result = result && (additional_properties == cr.additional_properties);
  result = result && (mortuary == cr.mortuary);
  result = result && (spell_knowledge == cr.spell_knowledge);

  return result;
}

void Creature::set_id(const string& new_id)
{
  id = new_id;
}

string Creature::get_id() const
{
  return id;
}

void Creature::set_original_id(const string& new_original_id)
{
  original_id = new_original_id;
}

string Creature::get_original_id() const
{
  return original_id;
}

void Creature::set_is_player(const bool player, ControllerPtr controller)
{
  is_player = player;

  // Only the player requires food.
  if (is_player)
  {
    hunger.set_requires_food(true);
  }

  decision_strategy.reset();

  if (player)
  {
    // Players always use the PlayerDecisionStrategy class so that keyboard input
    // can be used.
    decision_strategy = boost::make_shared<PlayerDecisionStrategy>(controller);

    // Players are always @s.
    set_symbol('@');
    
    // Players always use "player" as their ID.
    set_id(PlayerConstants::PLAYER_CREATURE_ID);
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

void Creature::set_handedness(const Handedness new_handedness)
{
  handedness = new_handedness;
}

Handedness Creature::get_handedness() const
{
  return handedness;
}

Handedness Creature::get_off_handedness() const
{
  if (handedness == RIGHT_HANDED)
  {
    return LEFT_HANDED;
  }
  else
  {
    return RIGHT_HANDED;
  }
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

void Creature::set_movement_accumulation(const MovementAccumulation& new_accumulation)
{
  movement_accumulation = new_accumulation;
}

MovementAccumulation& Creature::get_movement_accumulation_ref()
{
  return movement_accumulation;
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

void Creature::set_hit_points(const Statistic& new_hit_points)
{
  hit_points = new_hit_points;
}

int Creature::increment_hit_points(const int amount)
{
  hit_points.set_current(hit_points.get_current() + amount);
  return hit_points.get_current();
}

int Creature::decrement_hit_points(const int amount)
{
  hit_points.set_current(hit_points.get_current() - amount);
  return hit_points.get_current();
}

Statistic Creature::get_hit_points() const
{
  return hit_points;
}

bool Creature::is_hp_full() const
{
  return (hit_points.get_base() <= hit_points.get_current());
}

bool Creature::is_ap_full() const
{
  return (arcana_points.get_base() <= arcana_points.get_current());
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

void Creature::set_base_evade(const Statistic& new_base_evade)
{
  base_evade = new_base_evade;
}

Statistic Creature::get_base_evade() const
{
  return base_evade;
}

void Creature::set_base_soak(const Statistic& new_base_soak)
{
  base_soak = new_base_soak;
}

Statistic Creature::get_base_soak() const
{
  return base_soak;
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

bool Creature::hostile_to(const string& creature_id)
{
  DecisionStrategyPtr strategy = get_decision_strategy();
  
  if (strategy && strategy->get_threats().has_threat(creature_id))
  {
    return true;
  }

  return false;
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

DeityStatus& Creature::get_active_deity_status_ref()
{
  DeityRelations& relations = religion.get_deity_relations_ref();
  DeityStatus& status = relations[religion.get_active_deity_id()];
  return status;
}

void Creature::set_experience_value(const uint new_experience_value)
{
  experience_value = new_experience_value;
}

uint Creature::get_experience_value() const
{
  return experience_value;
}

void Creature::set_experience_points(const uint new_experience_points)
{
  experience_points = new_experience_points;
}

uint Creature::get_experience_points() const
{
  return experience_points;
}

void Creature::increment_turns()
{
  if (turns < numeric_limits<ulonglong>::max())
  {
    turns++;
  }
}

ulonglong Creature::get_turns() const
{
  return turns;
}

void Creature::set_target_map(const TargetMap& new_target_map)
{
  targets = new_target_map;
}

TargetMap Creature::get_target_map() const
{
  return targets;
}

TargetMap& Creature::get_target_map_ref()
{
  return targets;
}

void Creature::set_hunger_clock(const HungerClock& new_hunger_clock)
{
  hunger = new_hunger_clock;
}

HungerClock Creature::get_hunger_clock() const
{
  return hunger;
}

HungerClock& Creature::get_hunger_clock_ref()
{
  return hunger;
}

void Creature::clear_event_functions()
{
  event_functions.clear();
}

void Creature::set_event_functions(const EventFunctionMap& evm)
{
  event_functions = evm;
}

EventFunctionMap Creature::get_event_functions() const
{
  return event_functions;
}

void Creature::add_event_function(const string& event_name, const string& function_name)
{
  event_functions[event_name] = function_name;
}

bool Creature::has_event_function(const string& event_name)
{
  bool has_event = false;

  EventFunctionMap::iterator e_it = event_functions.find(event_name);

  if (e_it != event_functions.end())
  {
    has_event = true;
  }

  return has_event;
}

string Creature::get_event_function(const string& event_name) const
{
  string function_name;

  EventFunctionMap::const_iterator e_it = event_functions.find(event_name);

  if (e_it != event_functions.end())
  {
    function_name = e_it->second;
  }

  return function_name;
}

// Set and get the generic speech text sid.
void Creature::set_speech_text_sid(const string& speech_text_sid)
{
  additional_properties[CreatureAdditionalProperties::CREATURE_PROPERTY_SPEECH_TEXT_SID] = speech_text_sid;
}

string Creature::get_speech_text_sid() const
{
  string speech_text_sid;

  map<string, string>::const_iterator p_it = additional_properties.find(CreatureAdditionalProperties::CREATURE_PROPERTY_SPEECH_TEXT_SID);

  if (p_it != additional_properties.end())
  {
    speech_text_sid = p_it->second;
  }

  return speech_text_sid;
}

bool Creature::has_additional_property(const string& property_name) const
{
  bool has_property = false;

  if (additional_properties.find(property_name) != additional_properties.end())
  {
    has_property = true;
  }

  return has_property;
}

void Creature::set_additional_property(const string& property_name, const string& property_value)
{
  additional_properties[property_name] = property_value;
}

string Creature::get_additional_property(const string& property_name) const
{
  string property_value;

  map<string, string>::const_iterator p_it = additional_properties.find(property_name);

  if (p_it != additional_properties.end())
  {
    property_value = p_it->second;
  }

  return property_value;
}

void Creature::set_additional_properties_map(const map<string, string>& properties_map)
{
  additional_properties = properties_map;
}

map<string, string> Creature::get_additional_properties_map() const
{
  return additional_properties;
}

Mortuary& Creature::get_mortuary_ref()
{
  return mortuary;
}

void Creature::set_spell_knowledge(const SpellKnowledge& new_spell_knowledge)
{
  spell_knowledge = new_spell_knowledge;
}

SpellKnowledge& Creature::get_spell_knowledge_ref()
{
  return spell_knowledge;
}

// Set, get, and query additional (string) properties
  // Uncomment the code below to find out the size of Creature. :)
  // template<int s> struct creature_size;
  // creature_size<sizeof(Creature)> creature_size;

// Ensure that I haven't missed anything in the copy constructor, IO, etc!
void Creature::assert_size() const
{
  // VS 2010
  #ifdef _MSC_VER
    #ifdef _DEBUG
    // Debug
    BOOST_STATIC_ASSERT(sizeof(*this) == 840);
    #else
    // Release
    BOOST_STATIC_ASSERT(sizeof(*this) == 752);
    #endif
  #else // gcc toolchain
  BOOST_STATIC_ASSERT(sizeof(*this) == 424);
  #endif
}

// Swap values, no throw
void Creature::swap(Creature &cr) throw ()
{
  std::swap(this->id, cr.id);
  std::swap(this->original_id, cr.original_id);
  std::swap(this->is_player, cr.is_player);
  std::swap(this->name, cr.name);
  std::swap(this->sex, cr.sex);
  std::swap(this->age, cr.age);
  std::swap(this->size, cr.size);
  std::swap(this->eye_colour, cr.eye_colour);
  std::swap(this->hair_colour, cr.hair_colour);
  std::swap(this->handedness, cr.handedness);
  std::swap(this->short_description_sid, cr.short_description_sid);
  std::swap(this->description_sid, cr.description_sid);
  std::swap(this->race_id, cr.race_id);
  std::swap(this->class_id, cr.class_id);
  std::swap(this->strength, cr.strength);
  std::swap(this->dexterity, cr.dexterity);
  std::swap(this->agility, cr.agility);
  std::swap(this->health, cr.health);
  std::swap(this->intelligence, cr.intelligence);
  std::swap(this->willpower, cr.willpower);
  std::swap(this->charisma, cr.charisma);
  std::swap(this->valour, cr.valour);
  std::swap(this->spirit, cr.spirit);
  std::swap(this->speed, cr.speed);
  std::swap(this->damage, cr.damage);
  std::swap(this->equipment, cr.equipment);
  std::swap(this->inventory, cr.inventory);
  std::swap(this->resistances, cr.resistances);
  std::swap(this->skills, cr.skills);
  std::swap(this->movement_accumulation, cr.movement_accumulation);
  std::swap(this->hit_points, cr.hit_points);
  std::swap(this->arcana_points, cr.arcana_points);
  std::swap(this->base_evade, cr.base_evade);
  std::swap(this->base_soak, cr.base_soak);
  std::swap(this->evade, cr.evade);
  std::swap(this->soak, cr.soak);
  std::swap(this->symbol, cr.symbol);
  std::swap(this->colour, cr.colour);
  std::swap(this->level, cr.level);
  std::swap(this->decision_strategy, cr.decision_strategy);
  std::swap(this->religion, cr.religion);
  std::swap(this->experience_value, cr.experience_value);
  std::swap(this->experience_points, cr.experience_points);
  std::swap(this->turns, cr.turns);
  std::swap(this->targets, cr.targets);
  std::swap(this->hunger, cr.hunger);
  std::swap(this->event_functions, cr.event_functions);
  std::swap(this->additional_properties, cr.additional_properties);
  std::swap(this->mortuary, cr.mortuary);
  std::swap(this->spell_knowledge, cr.spell_knowledge);
}

bool Creature::serialize(ostream& stream)
{
  Serialize::write_string(stream, id);
  Serialize::write_string(stream, original_id);
  Serialize::write_bool(stream, is_player);

  Serialize::write_string(stream, name);
  Serialize::write_enum(stream, sex);
  age.serialize(stream);
  Serialize::write_enum(stream, size);
  Serialize::write_enum(stream, eye_colour);
  Serialize::write_enum(stream, hair_colour);
  Serialize::write_enum(stream, handedness);

  Serialize::write_string(stream, short_description_sid);
  Serialize::write_string(stream, description_sid);

  Serialize::write_string(stream, race_id);
  Serialize::write_string(stream, class_id);

  strength.serialize(stream);
  dexterity.serialize(stream);
  agility.serialize(stream);
  health.serialize(stream);
  intelligence.serialize(stream);
  willpower.serialize(stream);
  charisma.serialize(stream);

  valour.serialize(stream);
  spirit.serialize(stream);
  speed.serialize(stream);

  damage.serialize(stream);

  equipment.serialize(stream);
  inventory.serialize(stream);
  
  resistances.serialize(stream);

  skills.serialize(stream);

  movement_accumulation.serialize(stream);

  hit_points.serialize(stream);
  arcana_points.serialize(stream);

  base_evade.serialize(stream);
  base_soak.serialize(stream);
  evade.serialize(stream);
  soak.serialize(stream);

  Serialize::write_uchar(stream, symbol);
  Serialize::write_enum(stream, colour);

  level.serialize(stream);

  if (decision_strategy)
  {
    Serialize::write_class_id(stream, decision_strategy->get_class_identifier());
    decision_strategy->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, CLASS_ID_NULL);
  }

  religion.serialize(stream);

  Serialize::write_uint(stream, experience_value);
  Serialize::write_uint(stream, experience_points);
  Serialize::write_ulonglong(stream, turns);

  Serialize::write_size_t(stream, targets.size());

  BOOST_FOREACH(TargetMap::value_type& target_map_pair, targets)
  {
    Serialize::write_string(stream, target_map_pair.first);

    pair<string, Coordinate> target_pair = target_map_pair.second;

    Serialize::write_string(stream, target_pair.first);
    Serialize::write_int(stream, target_pair.second.first);
    Serialize::write_int(stream, target_pair.second.second);
  }

  hunger.serialize(stream);

  Serialize::write_size_t(stream, event_functions.size());

  if (!event_functions.empty())
  {
    BOOST_FOREACH(EventFunctionMap::value_type& event_function, event_functions)
    {
      Serialize::write_string(stream, event_function.first);
      Serialize::write_string(stream, event_function.second);
    }
  }

  Serialize::write_size_t(stream, additional_properties.size());

  if (!additional_properties.empty())
  {
    // Not "really" the type of the map from a conceptual standpoint...
    // But, it compiles!
    BOOST_FOREACH(EventFunctionMap::value_type& additional_property, additional_properties)
    {
      Serialize::write_string(stream, additional_property.first);
      Serialize::write_string(stream, additional_property.second);
    }
  }

  mortuary.serialize(stream);
  spell_knowledge.serialize(stream);

  return true;
}

bool Creature::deserialize(istream& stream)
{
  Serialize::read_string(stream, id);
  Serialize::read_string(stream, original_id);
  Serialize::read_bool(stream, is_player);

  Serialize::read_string(stream, name);
  Serialize::read_enum(stream, sex);
  age.deserialize(stream);
  Serialize::read_enum(stream, size);
  Serialize::read_enum(stream, eye_colour);
  Serialize::read_enum(stream, hair_colour);
  Serialize::read_enum(stream, handedness);

  Serialize::read_string(stream, short_description_sid);
  Serialize::read_string(stream, description_sid);
  
  Serialize::read_string(stream, race_id);
  Serialize::read_string(stream, class_id);

  strength.deserialize(stream);
  dexterity.deserialize(stream);
  agility.deserialize(stream);
  health.deserialize(stream);
  intelligence.deserialize(stream);
  willpower.deserialize(stream);
  charisma.deserialize(stream);

  valour.deserialize(stream);
  spirit.deserialize(stream);
  speed.deserialize(stream);

  damage.deserialize(stream);

  equipment.deserialize(stream);
  inventory.deserialize(stream);
  
  resistances.deserialize(stream);

  skills.deserialize(stream);

  movement_accumulation.deserialize(stream);

  hit_points.deserialize(stream);
  arcana_points.deserialize(stream);

  base_evade.deserialize(stream);
  base_soak.deserialize(stream);
  evade.deserialize(stream);
  soak.deserialize(stream);

  Serialize::read_uchar(stream, symbol);
  Serialize::read_enum(stream, colour);

  level.deserialize(stream);

  ClassIdentifier dc_clid = CLASS_ID_NULL;
  Serialize::read_class_id(stream, dc_clid);

  if (dc_clid != CLASS_ID_NULL)
  {
    decision_strategy = DecisionStrategyFactory::create_decision_strategy(dc_clid);
    if (!decision_strategy) return false;
    if (!decision_strategy->deserialize(stream)) return false;
  }

  religion.deserialize(stream);

  Serialize::read_uint(stream, experience_value);
  Serialize::read_uint(stream, experience_points);
  Serialize::read_ulonglong(stream, turns);

  size_t targets_size = 0;
  Serialize::read_size_t(stream, targets_size);

  targets.clear();

  for (unsigned int i = 0; i < targets_size; i++)
  {
    string attack_type;
    Serialize::read_string(stream, attack_type);

    string creature_id;
    Coordinate coord;
    Serialize::read_string(stream, creature_id);
    Serialize::read_int(stream, coord.first);
    Serialize::read_int(stream, coord.second);

    targets.insert(make_pair(attack_type, make_pair(creature_id, coord)));
  }

  hunger.deserialize(stream);

  size_t event_functions_size = 0;
  Serialize::read_size_t(stream, event_functions_size);

  if (event_functions_size > 0)
  {
    event_functions.clear();

    for (unsigned int i = 0; i < event_functions_size; i++)
    {
      string event_name, function_name;

      Serialize::read_string(stream, event_name);
      Serialize::read_string(stream, function_name);

      event_functions.insert(make_pair(event_name, function_name));
    }
  }

  size_t additional_properties_size = 0;
  Serialize::read_size_t(stream, additional_properties_size);

  if (additional_properties_size > 0)
  {
    additional_properties.clear();

    for (unsigned int i = 0; i < additional_properties_size; i++)
    {
      string prop_name, prop_value;

      Serialize::read_string(stream, prop_name);
      Serialize::read_string(stream, prop_value);

      additional_properties.insert(make_pair(prop_name, prop_value));
    }
  }

  mortuary.deserialize(stream);
  spell_knowledge.deserialize(stream);

  return true;
}

ClassIdentifier Creature::internal_class_identifier() const
{
  return CLASS_ID_CREATURE;
}

#ifdef UNIT_TESTS
#include "unit_tests/Creature_test.cpp"
#endif

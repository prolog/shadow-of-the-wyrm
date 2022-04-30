#include <limits>
#include "Conversion.hpp"
#include "Creature.hpp"
#include "CreatureProperties.hpp"
#include "DecisionStrategyFactory.hpp"
#include "DecisionStrategyProperties.hpp"
#include "InventoryFactory.hpp"
#include "PlayerDecisionStrategy.hpp"
#include "Serialize.hpp"
#include "ThreatConstants.hpp"
#include "Weapon.hpp"

using namespace std;

const int Creature::MAX_FREE_HIDDEN_ACTIONS = 2;
const int Creature::MAX_TRANSFERRABLE_FOLLOWERS = 8; // on stairs. exiting a map at the edges the max is 5.

// Set a reasonable set of default values for simple types, which are helpfully initialized to bullshit memory.
// Why did I write this in C++?
Creature::Creature()
: is_player(false)
, sex(CreatureSex::CREATURE_SEX_NOT_SPECIFIED)
, size(CreatureSize::CREATURE_SIZE_MEDIUM)
, eye_colour(EyeColour::EYE_COLOUR_BROWN)
, hair_colour(HairColour::HAIR_COLOUR_BLACK)
, handedness(Handedness::RIGHT_HANDED)
, breathes(BreatheType::BREATHE_TYPE_AIR)
, grams_unabsorbed_alcohol(0)
, symbol('?', Colour::COLOUR_WHITE)
, experience_value(0)
, experience_points(0)
, skill_points(0)
, turns(0)
// Everything else is a string, Statistic, etc, and is not a primitive type.  These'll have their own constructors.
// Religion defaults to atheist.
{
  inventory = std::make_shared<Inventory>();

  set_base_evade(0);
  set_base_soak(0);
  set_evade(0);
  set_soak (0);
  set_to_hit(0);
  set_addl_damage(0);
  
  // Base speed is 50.  This needs to be set or slimes get 25 actions to your 1 (23 or 24 if you're quick!).
  set_speed(50);

  // Ensure maximums are set for the primary statistics.
  strength.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);
  dexterity.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);
  agility.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);
  health.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);
  intelligence.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);
  willpower.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);
  charisma.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);

  Damage dam(1, 2, 0, DamageType::DAMAGE_TYPE_POUND, {}, false, false, false, false, false, false, false, false, 0, {});
  set_base_damage(dam);

  intrinsic_resistances.set_all_resistances_to(0);
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
  breathes = cr.breathes;
  blood = cr.blood;
  grams_unabsorbed_alcohol = cr.grams_unabsorbed_alcohol;
  alignment = cr.alignment;
  short_description_sid = cr.short_description_sid;
  description_sid = cr.description_sid;
  text_details_sid = cr.text_details_sid;
  race_id = cr.race_id;
  class_id = cr.class_id;
  strength = cr.strength;
  dexterity = cr.dexterity;
  agility = cr.agility;
  health = cr.health;
  intelligence = cr.intelligence;
  willpower = cr.willpower;
  charisma = cr.charisma;
  speed = cr.speed;
  damage = cr.damage;
  equipment = cr.equipment;
  inventory = cr.inventory;
  resistances = cr.resistances;
  intrinsic_resistances = cr.intrinsic_resistances;
  skills = cr.skills;
  movement_accumulation = cr.movement_accumulation;
  hit_points = cr.hit_points;
  arcana_points = cr.arcana_points;
  base_evade = cr.base_evade;
  base_soak = cr.base_soak;
  evade = cr.evade;
  soak = cr.soak;
  to_hit = cr.to_hit;
  addl_damage = cr.addl_damage;
  symbol = cr.symbol;
  level = cr.level;
  
  if (cr.decision_strategy)
  {
    // Without the copy constuctor, the raw pointer was being shared between creature instances,
    // and the threat map for supposedly peaceful creatures contained the player, making the creature hostile!
    decision_strategy = DecisionStrategyPtr(cr.decision_strategy->copy());
  }
  
  religion = cr.religion;
  experience_value = cr.experience_value;
  experience_points = cr.experience_points;
  skill_points = cr.skill_points;
  turns = cr.turns;
  targets = cr.targets;  
  hunger = cr.hunger;
  statuses = cr.statuses;
  event_scripts = cr.event_scripts;
  auto_move = cr.auto_move;
  additional_properties = cr.additional_properties;
  mortuary = cr.mortuary;
  conducts = cr.conducts;
  spell_knowledge = cr.spell_knowledge;
  modifiers = cr.modifiers;
  memberships = cr.memberships;
  max_depth_reached = cr.max_depth_reached;
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

bool Creature::operator==(const Creature& cr) const
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
  result = result && (breathes == cr.breathes);
  result = result && (blood == cr.blood);
  result = result && (grams_unabsorbed_alcohol == cr.grams_unabsorbed_alcohol);
  result = result && (alignment == cr.alignment);
  result = result && (short_description_sid == cr.short_description_sid);
  result = result && (description_sid == cr.description_sid);
  result = result && (text_details_sid == cr.text_details_sid);
  result = result && (race_id == cr.race_id);
  result = result && (class_id == cr.class_id);
  result = result && (strength == cr.strength);
  result = result && (dexterity == cr.dexterity);
  result = result && (agility == cr.agility);
  result = result && (health == cr.health);
  result = result && (intelligence == cr.intelligence);
  result = result && (willpower == cr.willpower);
  result = result && (charisma == cr.charisma);
  result = result && (speed == cr.speed);
  result = result && (damage == cr.damage);
  result = result && (equipment == cr.equipment);
  result = result && (inventory && cr.inventory && (*inventory == *(cr.inventory)));
  result = result && (resistances == cr.resistances);
  result = result && (intrinsic_resistances == cr.intrinsic_resistances);
  result = result && (skills == cr.skills);
  result = result && (movement_accumulation == cr.movement_accumulation);
  result = result && (hit_points == cr.hit_points);
  result = result && (arcana_points == cr.arcana_points);
  result = result && (base_evade == cr.base_evade);
  result = result && (evade == cr.evade);
  result = result && (base_soak == cr.base_soak);
  result = result && (soak == cr.soak);
  result = result && (to_hit == cr.to_hit);
  result = result && (addl_damage == cr.addl_damage);
  result = result && (symbol == cr.symbol);
  result = result && (level == cr.level);
  result = result && ((decision_strategy && cr.decision_strategy) || (!decision_strategy && !cr.decision_strategy));

  if (result && decision_strategy)
  {
    result = result && (*decision_strategy == *cr.decision_strategy);
  }

  result = result && (religion == cr.religion);
  result = result && (experience_value == cr.experience_value);
  result = result && (experience_points == cr.experience_points);
  result = result && (skill_points == cr.skill_points);
  result = result && (turns == cr.turns);
  result = result && (targets == cr.targets);
  result = result && (hunger == cr.hunger);
  result = result && (statuses == cr.statuses);
  result = result && (event_scripts == cr.event_scripts);
  result = result && (auto_move == cr.auto_move);
  result = result && (additional_properties == cr.additional_properties);
  result = result && (mortuary == cr.mortuary);
  result = result && (conducts == cr.conducts);
  result = result && (spell_knowledge == cr.spell_knowledge);
  result = result && (modifiers == cr.modifiers);
  result = result && (memberships == cr.memberships);
  result = result && (max_depth_reached == cr.max_depth_reached);

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

void Creature::set_is_player_flag(const bool player)
{
  is_player = player;
}

void Creature::set_is_player(const bool player, ControllerPtr controller)
{
  is_player = player;

  decision_strategy.reset();

  if (player)
  {
    // Players always use the PlayerDecisionStrategy class so that keyboard input
    // can be used.
    decision_strategy = std::make_unique<PlayerDecisionStrategy>(controller);

    // Players are always @s.
    Symbol s('@', Colour::COLOUR_WHITE);
    set_symbol(s);
    
    // Players always use "player" as their ID.
    set_id(CreatureID::CREATURE_ID_PLAYER);
  }
}

bool Creature::get_is_player() const
{
  return is_player;
}

// A creature "is" another creature if their ids match.
bool Creature::is(CreaturePtr other_creature) const
{
  bool is_other = false;

  if (other_creature != nullptr)
  {
    is_other = (id == other_creature->get_id());
  }

  return is_other;
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

string Creature::get_short_description_sid(const bool get_short_desc_only) const
{
  if (get_short_desc_only || name.empty())
  {
    return short_description_sid;
  }
  else
  {
    return name;
  }
}

void Creature::set_description_sid(const string& new_description_sid)
{
  description_sid = new_description_sid;
}

string Creature::get_description_sid(const bool get_desc_only) const
{
  if (get_desc_only || name.empty())
  {
    return description_sid;
  }
  else
  {
    return name;
  }
}

void Creature::set_text_details_sid(const string& new_text_details_sid)
{
  text_details_sid = new_text_details_sid;
}

string Creature::get_text_details_sid() const
{
  return text_details_sid;
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
  if (handedness == Handedness::RIGHT_HANDED)
  {
    return Handedness::LEFT_HANDED;
  }
  else
  {
    return Handedness::RIGHT_HANDED;
  }
}

void Creature::set_breathes(const BreatheType new_breathes)
{
  breathes = new_breathes;
}

BreatheType Creature::get_base_breathes() const
{
  return breathes;
}

vector<BreatheType> Creature::get_breathes() const
{
  vector<BreatheType> btypes = {breathes};

  if (breathes != BreatheType::BREATHE_TYPE_WATER && has_status(StatusIdentifiers::STATUS_ID_WATER_BREATHING))
  {
    btypes.push_back(BreatheType::BREATHE_TYPE_WATER);
  }
  
  return btypes;
}

bool Creature::can_breathe(const BreatheType btype) const
{
  if (breathes == BreatheType::BREATHE_TYPE_ALL)
  {
    return true;
  }

  if (btype == breathes || (btype == BreatheType::BREATHE_TYPE_WATER && has_status(StatusIdentifiers::STATUS_ID_WATER_BREATHING)))
  {
    return true;
  }

  return false;
}

void Creature::set_blood(const Blood& new_blood)
{
  blood = new_blood;
}

Blood Creature::get_blood() const
{
  return blood;
}

Blood& Creature::get_blood_ref()
{
  return blood;
}

void Creature::decrement_grams_unabsorbed_alcohol(const float delta_grams)
{
  grams_unabsorbed_alcohol -= delta_grams;
  grams_unabsorbed_alcohol = std::max<float>(grams_unabsorbed_alcohol, 0);
}

void Creature::increment_grams_unabsorbed_alcohol(const float addl_grams)
{
  grams_unabsorbed_alcohol += addl_grams;
}

void Creature::set_grams_unabsorbed_alcohol(const float new_grams_unabsorbed_alcohol)
{
  grams_unabsorbed_alcohol = new_grams_unabsorbed_alcohol;
}

float Creature::get_grams_unabsorbed_alcohol() const
{
  return grams_unabsorbed_alcohol;
}

void Creature::set_alignment(const Alignment& new_alignment)
{
  alignment = new_alignment;
}

Alignment Creature::get_alignment() const
{
  return alignment;
}

Alignment& Creature::get_alignment_ref()
{
  return alignment;
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
  strength.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);
}

Statistic& Creature::get_statistic_ref(const PrimaryStatisticType pr_st)
{
  switch(pr_st)
  {
    case PrimaryStatisticType::PRIMARY_STATISTIC_STRENGTH:
      return strength;
      break;
    case PrimaryStatisticType::PRIMARY_STATISTIC_DEXTERITY:
      return dexterity;
      break;
    case PrimaryStatisticType::PRIMARY_STATISTIC_AGILITY:
      return agility;
      break;
    case PrimaryStatisticType::PRIMARY_STATISTIC_HEALTH:
      return health;
      break;
    case PrimaryStatisticType::PRIMARY_STATISTIC_INTELLIGENCE:
      return intelligence;
      break;
    case PrimaryStatisticType::PRIMARY_STATISTIC_WILLPOWER:
      return willpower;
      break;
    case PrimaryStatisticType::PRIMARY_STATISTIC_CHARISMA:
    default:
      return charisma;
      break;
  }
}

Statistic Creature::get_strength() const
{
  return strength;
}

Statistic& Creature::get_strength_ref()
{
  return strength;
}

void Creature::set_dexterity(const Statistic& new_dexterity)
{
  dexterity = new_dexterity;
  dexterity.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);
}

Statistic Creature::get_dexterity() const
{
  return dexterity;
}

Statistic& Creature::get_dexterity_ref()
{
  return dexterity;
}

void Creature::set_agility(const Statistic& new_agility)
{
  agility = new_agility;
  agility.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);
}

Statistic Creature::get_agility() const
{
  return agility;
}

Statistic& Creature::get_agility_ref()
{
  return agility;
}

void Creature::set_health(const Statistic& new_health)
{
  health = new_health;
  health.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);
}

Statistic Creature::get_health() const
{
  return health;
}

Statistic& Creature::get_health_ref()
{
  return health;
}

void Creature::set_intelligence(const Statistic& new_intelligence)
{
  intelligence = new_intelligence;
  intelligence.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);
}

Statistic Creature::get_intelligence() const
{
  return intelligence;
}

Statistic& Creature::get_intelligence_ref()
{
  return intelligence;
}

void Creature::set_willpower(const Statistic& new_willpower)
{
  willpower = new_willpower;
  willpower.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);
}

Statistic Creature::get_willpower() const
{
  return willpower;
}

Statistic& Creature::get_willpower_ref()
{
  return willpower;
}

void Creature::set_charisma(const Statistic& new_charisma)
{
  charisma = new_charisma;
  charisma.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);
}

Statistic Creature::get_charisma() const
{
  return charisma;
}

Statistic& Creature::get_charisma_ref()
{
  return charisma;
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

void Creature::set_intrinsic_resistances(const Resistances& new_intrinsic_resistances)
{
  intrinsic_resistances = new_intrinsic_resistances;
}

Resistances& Creature::get_intrinsic_resistances_ref()
{
  return intrinsic_resistances;
}

Resistances Creature::get_intrinsic_resistances() const
{
  return intrinsic_resistances;
}

void Creature::set_skills(const Skills& new_skills)
{
  skills = new_skills;
}

Skills& Creature::get_skills()
{
  return skills;
}

bool Creature::can_learn_spells() const
{
  vector<SkillType> spell_categories = { SkillType::SKILL_MAGIC_CANTRIPS, SkillType::SKILL_MAGIC_ARCANE, SkillType::SKILL_MAGIC_DIVINE, SkillType::SKILL_MAGIC_MYSTIC, SkillType::SKILL_MAGIC_PRIMORDIAL };

  for (const SkillType spell_cat : spell_categories)
  {
    int skill_val = skills.get_value(spell_cat);

    if (skill_val > 0)
    {
      return true;
    }
  }

  return false;
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

int Creature::get_hands_available() const
{
  int hands_available = 2;
  vector<ItemPtr> wielded_items;

  wielded_items.push_back(equipment.get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED));
  wielded_items.push_back(equipment.get_item(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND));

  for (ItemPtr item : wielded_items)
  {
    if (item != nullptr)
    {
      // This is going to produce some odd results if I'm not careful.
      hands_available -= item->get_hands_required();
    }
  }

  return hands_available;
}

IInventoryPtr Creature::get_inventory()
{
  return inventory;
}

// Currency counts towards total weight, but not total items.
uint Creature::get_weight_carried() const
{
  uint total_weight = 0;

  for (int e = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); e < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); e++)
  {
    EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(e);
    ItemPtr item = equipment.get_item(ewl);

    if (item != nullptr)
    {
      total_weight += item->get_total_weight().get_weight();
    }
  }

  if (inventory != nullptr)
  {
    const list<ItemPtr> items = inventory->get_items_cref();

    for (ItemPtr item : items)
    {
      if (item != nullptr)
      {
        total_weight += (item->get_quantity() * item->get_weight().get_weight());
      }
    }
  }

  return total_weight;
}

bool Creature::has_items() const
{
  for (int e = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); e < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); e++)
  {
    EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(e);
    ItemPtr item = equipment.get_item(ewl);
    if (item != nullptr) return true;
  }

  if (inventory->has_items())
  {
    return true;
  }

  return false;
}

bool Creature::has_unpaid_items() const
{
  for (int e = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); e < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); e++)
  {
    EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(e);
    ItemPtr item = equipment.get_item(ewl);
    if (item != nullptr && item->get_unpaid())
    {
      return true;
    }
  }

  if (inventory != nullptr)
  {
    return inventory->has_unpaid_items();
  }

  return false;
}

bool Creature::has_item_with_property(const std::string& prop_name) const
{
  for (int e = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); e < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); e++)
  {
    EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(e);
    ItemPtr item = equipment.get_item(ewl);
    if (item != nullptr && item->has_additional_property(prop_name))
    {
      return true;
    }
  }

  if (inventory != nullptr)
  {
    return inventory->has_item_with_property(prop_name);
  }

  return false;
}

uint Creature::count_items() const
{
  uint count = equipment.count_items() + inventory->count_items();
  return count;
}

uint Creature::get_unpaid_amount() const
{
  uint total = 0;

  for (int e = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); e < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); e++)
  {
    EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(e);
    ItemPtr item = equipment.get_item(ewl);
    if (item != nullptr && item->get_unpaid())
    {
      total += item->get_total_value();
    }
  }

  if (inventory != nullptr)
  {
    const list<ItemPtr> raw_items = inventory->get_items_cref();

    for (ItemPtr item : raw_items)
    {
      if (item && item->get_unpaid())
      {
        total += item->get_total_value();
      }
    }
  }

  return total;
}

void Creature::set_items_paid()
{
  for (int e = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); e < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); e++)
  {
    EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(e);
    ItemPtr item = equipment.get_item(ewl);
    if (item != nullptr)
    {
      item->set_unpaid(false);
    }
  }

  if (inventory != nullptr)
  {
    const list<ItemPtr> raw_items = inventory->get_items_cref();

    for (ItemPtr item : raw_items)
    {
      if (item)
      {
        item->set_unpaid(false);
      }
    }
  }
}

// After a creature identifies items, or blesses something, or whatever, the
// inventory needs to be restacked so that items form the appropriate groups.
void Creature::restack_items()
{
  IInventoryPtr new_items = std::make_shared<Inventory>();
  list<ItemPtr> raw_items = inventory->get_items_ref();

  for (ItemPtr i : raw_items)
  {
    if (i != nullptr)
    {
      new_items->merge_or_add(i, InventoryAdditionType::INVENTORY_ADDITION_BACK);
    }
  }

  inventory = new_items;
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

Statistic& Creature::get_hit_points_ref()
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

bool Creature::is_dead() const
{
  return (hit_points.get_current() <= 0);
}

void Creature::set_arcana_points(const Statistic& new_arcana_points)
{
  arcana_points = new_arcana_points;
}

int Creature::increment_arcana_points(const int amount)
{
  arcana_points.set_current(arcana_points.get_current() + amount);
  return arcana_points.get_current();
}

int Creature::decrement_arcana_points(const int amount)
{
  arcana_points.set_current(arcana_points.get_current() - amount);
  return arcana_points.get_current();
}

Statistic Creature::get_arcana_points() const
{
  return arcana_points;
}

Statistic& Creature::get_arcana_points_ref()
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

void Creature::set_to_hit(const Statistic& new_to_hit)
{
  to_hit = new_to_hit;
}

Statistic Creature::get_to_hit() const
{
  return to_hit;
}

void Creature::set_addl_damage(const Statistic& new_addl_damage)
{
  addl_damage = new_addl_damage;
}

Statistic Creature::get_addl_damage() const
{
  return addl_damage;
}

void Creature::set_symbol(const Symbol& new_symbol)
{
  symbol = new_symbol;
}

Symbol Creature::get_symbol() const
{
  return symbol;
}

Symbol& Creature::get_symbol_ref()
{
  return symbol;
}

void Creature::set_level(const Statistic& new_level)
{
  level = new_level;
}

Statistic Creature::get_level() const
{
  return level;
}

void Creature::set_decision_strategy(DecisionStrategyPtr strategy)
{
  decision_strategy = std::move(strategy);
}

DecisionStrategy* Creature::get_decision_strategy() const
{
  return decision_strategy.get();
}

DecisionStrategyPtr Creature::get_decision_strategy_uptr()
{
  return std::move(decision_strategy);
}

void Creature::set_leader_and_at_ease(const std::string& leader_id)
{
  set_additional_property(CreatureProperties::CREATURE_PROPERTIES_LEADER_ID, leader_id);

  if (decision_strategy != nullptr)
  {
    ThreatRatings& threats = decision_strategy->get_threats_ref();
    auto rating = threats.has_threat(leader_id);

    if (rating.first)
    {
      decision_strategy->get_threats_ref().remove_threat(leader_id, rating.second);
    }

    decision_strategy->set_property(DecisionStrategyProperties::DECISION_STRATEGY_AT_EASE, std::to_string(true));
  }
}

void Creature::remove_leader()
{
  remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_LEADER_ID);

  if (decision_strategy != nullptr)
  {
    decision_strategy->remove_property(DecisionStrategyProperties::DECISION_STRATEGY_FOLLOW_CREATURE_ID);
  }
}

bool Creature::has_leader() const
{
  string leader_id = get_leader_id();
  return (!leader_id.empty());
}

string Creature::get_leader_id() const
{
  return get_additional_property(CreatureProperties::CREATURE_PROPERTIES_LEADER_ID);
}

bool Creature::is_leader(CreaturePtr cr) const
{
  bool leader = false;

  if (cr != nullptr)
  {
    leader = (id == cr->get_leader_id());
  }

  return leader;
}

bool Creature::hostile_to(const string& creature_id)
{
  DecisionStrategy* strategy = get_decision_strategy();
  pair<bool, int> threat_details = strategy->get_threats().has_threat(creature_id);

  // Ensure that we only return creatures that are beyond the "dislike"
  // threhold - these are the creatures that the current creature is
  // truly hostile towards.
  if (strategy && threat_details.first && threat_details.second > ThreatConstants::DISLIKE_THREAT_RATING)
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
  // Only set experience if we've not yet hit the max level.
  if (level.get_current() < static_cast<int>(CreatureConstants::MAX_CREATURE_LEVEL))
  {
    experience_points = new_experience_points;
  }
}

uint Creature::get_experience_points() const
{
  return experience_points;
}

void Creature::set_skill_points(const int new_skill_points)
{
  skill_points = new_skill_points;
}

void Creature::increment_skill_points(const int incr_amount)
{
  skill_points += incr_amount;
}

int Creature::get_skill_points() const
{
  return skill_points;
}

void Creature::increment_turns()
{
  if (turns < std::numeric_limits<ulonglong>::max())
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

void Creature::set_status(const string& status_id, const Status& status)
{
  statuses[status_id] = status;
}

bool Creature::remove_status(const string& status_id)
{
  set<string> am_status_ids = get_active_modifier_status_ids();

  if (am_status_ids.find(status_id) == am_status_ids.end())
  {
    statuses.erase(status_id);
    return true;
  }

  return false;
}

bool Creature::has_status(const string& status_id) const
{
  bool has_status = false;

  CreatureStatusMap::const_iterator s_it = statuses.find(status_id);

  if (s_it != statuses.end())
  {
    has_status = (s_it->second.get_value() == true);
  }

  return has_status;
}

bool Creature::has_status() const
{
  return !statuses.empty();
}

void Creature::set_statuses(const CreatureStatusMap& new_statuses)
{
  statuses = new_statuses;
}

CreatureStatusMap Creature::get_statuses() const
{
  return statuses;
}

CreatureStatusMap& Creature::get_statuses_ref()
{
  return statuses;
}

Status Creature::get_status(const string& status_id) const
{
  Status st;
  auto s_it = statuses.find(status_id);

  if (s_it != statuses.end())
  {
    st = s_it->second;
  }

  return st;
}

void Creature::clear_event_scripts()
{
  event_scripts.clear();
}

void Creature::set_event_scripts(const EventScriptsMap& esm)
{
  event_scripts = esm;
}

EventScriptsMap Creature::get_event_scripts() const
{
  return event_scripts;
}

EventScriptsMap& Creature::get_event_scripts_ref()
{
  return event_scripts;
}

void Creature::add_event_script(const string& event_name, const ScriptDetails& sd)
{
  event_scripts[event_name] = sd;
}

void Creature::remove_event_script(const string& event_name)
{
  auto e_it = event_scripts.find(event_name);

  if (e_it != event_scripts.end())
  {
    event_scripts.erase(e_it);
  }
}

bool Creature::has_event_script(const string& event_name)
{
  bool has_event = false;

  EventScriptsMap::iterator e_it = event_scripts.find(event_name);

  if (e_it != event_scripts.end())
  {
    has_event = true;
  }

  return has_event;
}

ScriptDetails Creature::get_event_script(const string& event_name) const
{
  ScriptDetails sd;

  EventScriptsMap::const_iterator e_it = event_scripts.find(event_name);

  if (e_it != event_scripts.end())
  {
    sd = e_it->second;
  }

  return sd;
}

// Set and get the generic speech text sid.
void Creature::set_speech_text_sid(const string& speech_text_sid)
{
  additional_properties[CreatureProperties::CREATURE_PROPERTIES_SPEECH_TEXT_SID] = speech_text_sid;
}

string Creature::get_speech_text_sid() const
{
  string speech_text_sid;

  map<string, string>::const_iterator p_it = additional_properties.find(CreatureProperties::CREATURE_PROPERTIES_SPEECH_TEXT_SID);

  if (p_it != additional_properties.end())
  {
    speech_text_sid = p_it->second;
  }

  return speech_text_sid;
}

void Creature::set_automatic_movement(const AutomaticMovement& new_auto_move)
{
  auto_move = new_auto_move;
}

AutomaticMovement& Creature::get_automatic_movement_ref()
{
  return auto_move;
}

vector<CreatureWin> Creature::get_satisfied_win_conditions() const
{
  vector<CreatureWin> wins;

  static_assert(CreatureWin::CREATURE_WIN_LAST == CreatureWin(3), "Unexpected CreatureWin::CREATURE_WIN_LAST!");
  vector<CreatureWin> win_conditions = {CreatureWin::CREATURE_WIN_REGULAR, CreatureWin::CREATURE_WIN_EVIL, CreatureWin::CREATURE_WIN_GODSLAYER};

  for (const CreatureWin win : win_conditions)
  {
    string p_key = CreatureProperties::CREATURE_PROPERTIES_WINNER + "_" + to_string(static_cast<int>(win));
    string p_val = get_additional_property(p_key);

    if (!p_val.empty() && String::to_bool(p_val))
    {
      wins.push_back(win);
    }
  }

  return wins;
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

void Creature::remove_additional_property(const string& property_name)
{
  additional_properties.erase(property_name);
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

Conducts& Creature::get_conducts_ref()
{
  return conducts;
}

void Creature::set_spell_knowledge(const SpellKnowledge& new_spell_knowledge)
{
  spell_knowledge = new_spell_knowledge;
}

SpellKnowledge& Creature::get_spell_knowledge_ref()
{
  return spell_knowledge;
}

SpellKnowledge Creature::get_spell_knowledge() const
{
  return spell_knowledge;
}

void Creature::set_free_hidden_actions(const int new_actions)
{
  if (new_actions >= 0)
  {
    set_additional_property(CreatureProperties::CREATURE_PROPERTIES_FREE_HIDDEN_ACTIONS, to_string(new_actions));
  }
}

// Increment the number of free hidden actions, returning the value.
int Creature::increment_free_hidden_actions()
{
  int val = 0;

  val = get_free_hidden_actions() + 1;

  if (val > MAX_FREE_HIDDEN_ACTIONS)
  {
    val = MAX_FREE_HIDDEN_ACTIONS;
  }

  set_free_hidden_actions(val);

  return val;
}

// Decrement the number of free hidden actions, returning the value.
int Creature::decrement_free_hidden_actions()
{
  int val = 0;

  val = get_free_hidden_actions() - 1;

  if (val > 0)
  {
    set_free_hidden_actions(val);
  }
  else
  {
    val = 0;
    remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_FREE_HIDDEN_ACTIONS);
  }

  return val;
}

int Creature::get_free_hidden_actions() const
{
  int hidden_cnt = 0;

  string hidden_s = get_additional_property(CreatureProperties::CREATURE_PROPERTIES_FREE_HIDDEN_ACTIONS);
  if (!hidden_s.empty())
  {
    hidden_cnt = String::to_int(hidden_s);
  }

  return hidden_cnt;
}


void Creature::set_modifiers(const map<double, vector<pair<string, Modifier>>>& new_modifiers)
{
  modifiers = new_modifiers;
}

// Get only the active modifiers.  Active modifiers are those
// not marked for deletion.
map<double, vector<pair<string, Modifier>>> Creature::get_active_modifiers() const
{
  map<double, vector<pair<string, Modifier>>> active_modifiers;

  for (const auto& modifiers_pair : modifiers)
  {
    vector<pair<string, Modifier>> mod_vec;

    for (const auto& mod_pair : modifiers_pair.second)
    {
      if (mod_pair.second.get_delete() == false)
      {
        mod_vec.push_back(mod_pair);
      }
    }

    if (!mod_vec.empty())
    {
      active_modifiers[modifiers_pair.first] = mod_vec;
    }
  }

  return active_modifiers;
}

map<double, vector<pair<string, Modifier>>> Creature::get_modifiers() const
{
  return modifiers;
}

map<double, vector<pair<string, Modifier>>>& Creature::get_modifiers_ref()
{
  return modifiers;
}

bool Creature::is_affected_by_modifier_spell(const std::string& spell_id) const
{
  // If there's no spell ID (ie, if it's just a status effect like poison,
  // etc) return false.
  if (spell_id.empty())
  {
    return false;
  }

  auto active_modifiers = get_active_modifiers();

  for (const auto& pair : active_modifiers)
  {
    for (const auto& spells : pair.second)
    {
      if (spells.first == spell_id)
      {
        return true;
      }
    }
  }

  return false;
}

void Creature::set_memberships(const Memberships& new_memberships)
{
  memberships = new_memberships;
}

Memberships Creature::get_memberships() const
{
  return memberships;
}

Memberships& Creature::get_memberships_ref()
{
  return memberships;
}

// Set, get, and query additional (string) properties
// Uncomment the code below to find out the size of Creature. :)
//template<int s> struct creature_size;
//creature_size<sizeof(Creature)> creature_size;

// Ensure that I haven't missed anything in the copy constructor, IO, etc!
void Creature::assert_size() const
{
  // Visual Studio
  #ifdef _MSC_VER
    #ifdef _DEBUG
    // Debug
    static_assert(sizeof(*this) == 1376, "Unexpected sizeof Creature.");
    #else
    // Release
    static_assert(sizeof(*this) == 1264, "Unexpected sizeof Creature.");
    #endif
  #else // gcc toolchain
  // Works for gcc in release
  static_assert(sizeof(*this) == 2296 || sizeof(*this) == 1720, "Unexpected sizeof Creature.");
  #endif
}

// Convenience function that calls the functions on the decision strategy.
bool Creature::has_creature_in_view(const string& creature_id) const
{
  bool has_cr = false;

  if (decision_strategy != nullptr)
  {
    MapPtr fov_map = decision_strategy->get_fov_map();

    if (fov_map != nullptr)
    {
      has_cr = fov_map->has_creature(creature_id);
    }
  }

  return has_cr;
}

// Is the creature a procedurally-generated ancient beast?
bool Creature::is_ancient_beast(const string& id)
{
  string prefix = CreatureID::CREATURE_ID_PREFIX_ANCIENT_BEAST;
  return (id.compare(0, prefix.size(), prefix) == 0);
}

void Creature::set_max_depth_reached(const Depth& new_depth)
{
  max_depth_reached = new_depth;
}

Depth Creature::get_max_depth_reached() const
{
  return max_depth_reached;
}

void Creature::set_hirelings_hired(const int new_hirelings_hired)
{
  set_additional_property(CreatureProperties::CREATURE_PROPERTIES_HIRELINGS_HIRED, std::to_string(new_hirelings_hired));
}

int Creature::get_hirelings_hired() const
{
  int hirelings_hired = 0;
  string hired_s = get_additional_property(CreatureProperties::CREATURE_PROPERTIES_HIRELINGS_HIRED);

  if (!hired_s.empty())
  {
    hirelings_hired = String::to_int(hired_s);
  }

  return hirelings_hired;
}

void Creature::set_adventurers_joined(const int new_adventurers_joined)
{
  set_additional_property(CreatureProperties::CREATURE_PROPERTIES_ADVENTURERS_JOINED, std::to_string(new_adventurers_joined));
}

int Creature::get_adventurers_joined() const
{
  int adv_joined = 0;
  string joined_s = get_additional_property(CreatureProperties::CREATURE_PROPERTIES_ADVENTURERS_JOINED);

  if (!joined_s.empty())
  {
    adv_joined = String::to_int(joined_s);
  }

  return adv_joined;
}

bool Creature::is_allied_to(const string& creature_id) const
{
  bool allied = false;

  if (decision_strategy != nullptr)
  {
    vector<string> allies = String::create_string_vector_from_csv_string(decision_strategy->get_property(DecisionStrategyProperties::DECISION_STRATEGY_ALLIES_IDS));

    if (std::find(allies.begin(), allies.end(), creature_id) != allies.end())
    {
      allied = true;
    }
  }

  return allied;
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
  std::swap(this->breathes, cr.breathes);
  std::swap(this->blood, cr.blood);
  std::swap(this->grams_unabsorbed_alcohol, cr.grams_unabsorbed_alcohol);
  std::swap(this->alignment, cr.alignment);
  std::swap(this->short_description_sid, cr.short_description_sid);
  std::swap(this->description_sid, cr.description_sid);
  std::swap(this->text_details_sid, cr.text_details_sid);
  std::swap(this->race_id, cr.race_id);
  std::swap(this->class_id, cr.class_id);
  std::swap(this->strength, cr.strength);
  std::swap(this->dexterity, cr.dexterity);
  std::swap(this->agility, cr.agility);
  std::swap(this->health, cr.health);
  std::swap(this->intelligence, cr.intelligence);
  std::swap(this->willpower, cr.willpower);
  std::swap(this->charisma, cr.charisma);
  std::swap(this->speed, cr.speed);
  std::swap(this->damage, cr.damage);
  std::swap(this->equipment, cr.equipment);
  std::swap(this->inventory, cr.inventory);
  std::swap(this->resistances, cr.resistances);
  std::swap(this->intrinsic_resistances, cr.intrinsic_resistances);
  std::swap(this->skills, cr.skills);
  std::swap(this->movement_accumulation, cr.movement_accumulation);
  std::swap(this->hit_points, cr.hit_points);
  std::swap(this->arcana_points, cr.arcana_points);
  std::swap(this->base_evade, cr.base_evade);
  std::swap(this->base_soak, cr.base_soak);
  std::swap(this->evade, cr.evade);
  std::swap(this->soak, cr.soak);
  std::swap(this->to_hit, cr.to_hit);
  std::swap(this->addl_damage, cr.addl_damage);
  std::swap(this->symbol, cr.symbol);
  std::swap(this->level, cr.level);
  std::swap(this->decision_strategy, cr.decision_strategy);
  std::swap(this->religion, cr.religion);
  std::swap(this->experience_value, cr.experience_value);
  std::swap(this->experience_points, cr.experience_points);
  std::swap(this->skill_points, cr.skill_points);
  std::swap(this->turns, cr.turns);
  std::swap(this->targets, cr.targets);
  std::swap(this->hunger, cr.hunger);
  std::swap(this->statuses, cr.statuses);
  std::swap(this->event_scripts, cr.event_scripts);
  std::swap(this->auto_move, cr.auto_move);
  std::swap(this->additional_properties, cr.additional_properties);
  std::swap(this->mortuary, cr.mortuary);
  std::swap(this->conducts, cr.conducts);
  std::swap(this->spell_knowledge, cr.spell_knowledge);
  std::swap(this->modifiers, cr.modifiers);
  std::swap(this->memberships, cr.memberships);
  std::swap(this->max_depth_reached, cr.max_depth_reached);
}

bool Creature::serialize(ostream& stream) const
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
  Serialize::write_enum(stream, breathes);
  blood.serialize(stream);
  Serialize::write_float(stream, grams_unabsorbed_alcohol);
  alignment.serialize(stream);

  Serialize::write_string(stream, short_description_sid);
  Serialize::write_string(stream, description_sid);
  Serialize::write_string(stream, text_details_sid);

  Serialize::write_string(stream, race_id);
  Serialize::write_string(stream, class_id);

  strength.serialize(stream);
  dexterity.serialize(stream);
  agility.serialize(stream);
  health.serialize(stream);
  intelligence.serialize(stream);
  willpower.serialize(stream);
  charisma.serialize(stream);

  speed.serialize(stream);

  damage.serialize(stream);

  equipment.serialize(stream);
  
  Serialize::write_class_id(stream, inventory->get_class_identifier());
  inventory->serialize(stream);
  
  resistances.serialize(stream);
  intrinsic_resistances.serialize(stream);

  skills.serialize(stream);

  movement_accumulation.serialize(stream);

  hit_points.serialize(stream);
  arcana_points.serialize(stream);

  base_evade.serialize(stream);
  base_soak.serialize(stream);
  evade.serialize(stream);
  soak.serialize(stream);

  to_hit.serialize(stream);
  addl_damage.serialize(stream);
  symbol.serialize(stream);
  level.serialize(stream);

  if (decision_strategy)
  {
    Serialize::write_class_id(stream, decision_strategy->get_class_identifier());
    decision_strategy->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
  }

  religion.serialize(stream);

  Serialize::write_uint(stream, experience_value);
  Serialize::write_uint(stream, experience_points);
  Serialize::write_int(stream, skill_points);
  Serialize::write_ulonglong(stream, turns);

  Serialize::write_size_t(stream, targets.size());

  for (const TargetMap::value_type& target_map_pair : targets)
  {
    Serialize::write_string(stream, target_map_pair.first);

    pair<string, Coordinate> target_pair = target_map_pair.second;

    Serialize::write_string(stream, target_pair.first);
    Serialize::write_int(stream, target_pair.second.first);
    Serialize::write_int(stream, target_pair.second.second);
  }

  hunger.serialize(stream);

  Serialize::write_size_t(stream, statuses.size());

  if (!statuses.empty())
  {
    for (const CreatureStatusMap::value_type& c_status : statuses)
    {
      Serialize::write_string(stream, c_status.first);
      c_status.second.serialize(stream);
    }
  }

  Serialize::write_event_scripts(stream, event_scripts);

  auto_move.serialize(stream);

  Serialize::write_string_map(stream, additional_properties);

  mortuary.serialize(stream);
  conducts.serialize(stream);
  spell_knowledge.serialize(stream);

  size_t m_size = modifiers.size();
  Serialize::write_size_t(stream, m_size);
  for (auto& m_pair : modifiers)
  {
    Serialize::write_double(stream, m_pair.first);

    Serialize::write_size_t(stream, m_pair.second.size());
    for (auto& m_element : m_pair.second)
    {
      Serialize::write_string(stream, m_element.first);
      m_element.second.serialize(stream);
    }
  }

  memberships.serialize(stream);
  max_depth_reached.serialize(stream);

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
  Serialize::read_enum(stream, breathes);
  blood.deserialize(stream);
  Serialize::read_float(stream, grams_unabsorbed_alcohol);
  alignment.deserialize(stream);

  Serialize::read_string(stream, short_description_sid);
  Serialize::read_string(stream, description_sid);
  Serialize::read_string(stream, text_details_sid);
  
  Serialize::read_string(stream, race_id);
  Serialize::read_string(stream, class_id);

  strength.deserialize(stream);
  dexterity.deserialize(stream);
  agility.deserialize(stream);
  health.deserialize(stream);
  intelligence.deserialize(stream);
  willpower.deserialize(stream);
  charisma.deserialize(stream);

  speed.deserialize(stream);

  damage.deserialize(stream);

  equipment.deserialize(stream);

  ClassIdentifier inv_class_id;
  Serialize::read_class_id(stream, inv_class_id);

  inventory = InventoryFactory::create_inventory(inv_class_id);
  inventory->deserialize(stream);
  
  resistances.deserialize(stream);
  intrinsic_resistances.deserialize(stream);

  skills.deserialize(stream);

  movement_accumulation.deserialize(stream);

  hit_points.deserialize(stream);
  arcana_points.deserialize(stream);

  base_evade.deserialize(stream);
  base_soak.deserialize(stream);
  evade.deserialize(stream);
  soak.deserialize(stream);

  to_hit.deserialize(stream);
  addl_damage.deserialize(stream);
  symbol.deserialize(stream);
  level.deserialize(stream);

  ClassIdentifier dc_clid = ClassIdentifier::CLASS_ID_NULL;
  Serialize::read_class_id(stream, dc_clid);

  if (dc_clid != ClassIdentifier::CLASS_ID_NULL)
  {
    decision_strategy = DecisionStrategyFactory::create_decision_strategy(dc_clid);
    if (!decision_strategy) return false;
    if (!decision_strategy->deserialize(stream)) return false;
  }

  religion.deserialize(stream);

  Serialize::read_uint(stream, experience_value);
  Serialize::read_uint(stream, experience_points);
  Serialize::read_int(stream, skill_points);
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

  size_t statuses_size = 0;
  Serialize::read_size_t(stream, statuses_size);

  if (statuses_size > 0)
  {
    statuses.clear();

    for (unsigned int i = 0; i < statuses_size; i++)
    {
      string c_status_id;
      Status status;

      Serialize::read_string(stream, c_status_id);
      status.deserialize(stream);

      statuses[c_status_id] = status;
    }
  }

  Serialize::read_event_scripts(stream, event_scripts);

  auto_move.deserialize(stream);

  Serialize::read_string_map(stream, additional_properties);

  mortuary.deserialize(stream);
  conducts.deserialize(stream);
  spell_knowledge.deserialize(stream);

  size_t sm_size = 0;
  Serialize::read_size_t(stream, sm_size);
  for (size_t i = 0; i < sm_size; i++)
  {
    double elapsed = 0;
    Serialize::read_double(stream, elapsed);

    size_t vec_size = 0;
    vector<pair<string, Modifier>> m_vec;
    Serialize::read_size_t(stream, vec_size);

    for (size_t j = 0; j < vec_size; j++)
    {
      string spell_id;
      Serialize::read_string(stream, spell_id);

      Modifier m;
      m.deserialize(stream);

      m_vec.push_back(make_pair(spell_id, m));
    }

    modifiers.insert(make_pair(elapsed, m_vec));
  }

  memberships.deserialize(stream);
  max_depth_reached.deserialize(stream);

  return true;
}

ClassIdentifier Creature::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CREATURE;
}

set<string> Creature::get_active_modifier_status_ids() const
{
  set<string> status_ids;
  auto active_mods = get_active_modifiers();

  for (auto m_details : active_mods)
  {
    auto m_list = m_details.second;

    for (auto mods : m_list)
    {
      auto statuses = mods.second.get_affected_statuses();

      for (auto s_details : statuses)
      {
        status_ids.insert(s_details.first);
      }
    }
  }

  return status_ids;
}

#ifdef UNIT_TESTS
#include "unit_tests/Creature_test.cpp"
#endif

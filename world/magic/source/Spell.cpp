#include "Spell.hpp"

using namespace std;

Spell::Spell()
: magic_category(SkillType::SKILL_MAGIC_ARCANE), 
colour(Colour::COLOUR_WHITE),
  ap_cost(0), 
  speed(1), 
  range(0), 
  has_damage(false),
  allows_bonus(true),
  effect(EffectType::EFFECT_TYPE_NULL)
{
}

bool Spell::operator==(const Spell& spell) const
{
  bool result = true;

  result = result && (spell_id == spell.spell_id);
  result = result && (spell_name_sid == spell.spell_name_sid);
  result = result && (player_cast_message_sid == spell.player_cast_message_sid);
  result = result && (monster_cast_message_sid == spell.monster_cast_message_sid);
  result = result && (magic_category == spell.magic_category);
  result = result && (colour == spell.colour);
  result = result && (ap_cost == spell.ap_cost);
  result = result && (speed == spell.speed);
  result = result && (range == spell.range);
  result = result && (shape == spell.shape);
  result = result && (has_damage == spell.has_damage);
  result = result && (damage == spell.damage);
  result = result && (allows_bonus == spell.allows_bonus);
  result = result && (effect == spell.effect);
  result = result && (modifier == spell.modifier);
  result = result && (properties == spell.properties);

  return result;
}

void Spell::set_spell_id(const string& new_spell_id)
{
  spell_id = new_spell_id;
}

string Spell::get_spell_id() const
{
  return spell_id;
}

void Spell::set_spell_name_sid(const string& new_spell_name_sid)
{
  spell_name_sid = new_spell_name_sid;
}

void Spell::set_player_cast_message_sid(const string& new_player_cast_message_sid)
{
  player_cast_message_sid = new_player_cast_message_sid;
}

string Spell::get_player_cast_message_sid() const
{
  return player_cast_message_sid;
}

void Spell::set_monster_cast_message_sid(const string& new_monster_cast_message_sid)
{
  monster_cast_message_sid = new_monster_cast_message_sid;
}

string Spell::get_monster_cast_message_sid() const
{
  return monster_cast_message_sid;
}

string Spell::get_spell_name_sid() const
{
  return spell_name_sid;
}

void Spell::set_magic_category(const SkillType new_magic_category)
{
  magic_category = new_magic_category;
}

SkillType Spell::get_magic_category() const
{
  return magic_category;
}

void Spell::set_colour(const Colour new_colour)
{
  colour = new_colour;
}

Colour Spell::get_colour() const
{
  return colour;
}

void Spell::set_ap_cost(const uint new_ap_cost)
{
  ap_cost = new_ap_cost;
}

uint Spell::get_ap_cost() const
{
  return ap_cost;
}

void Spell::set_speed(const int new_speed)
{
  speed = new_speed;
}

int Spell::get_speed() const
{
  return speed;
}

void Spell::set_range(const uint new_range)
{
  range = new_range;
}

uint Spell::get_range() const
{
  return range;
}

void Spell::set_shape(const SpellShape& new_shape)
{
  shape = new_shape;
}

SpellShape Spell::get_shape() const
{
  return shape;
}

void Spell::set_has_damage(const bool new_has_damage)
{
  has_damage = new_has_damage;
}

bool Spell::get_has_damage() const
{
  return has_damage;
}

void Spell::set_damage(const Damage& new_damage)
{
  damage = new_damage;
}

Damage Spell::get_damage() const
{
  return damage;
}

void Spell::set_allows_bonus(const bool new_allows_bonus)
{
  allows_bonus = new_allows_bonus;
}

bool Spell::get_allows_bonus() const
{
  return allows_bonus;
}

void Spell::set_effect(const EffectType new_effect)
{
  effect = new_effect;
}

EffectType Spell::get_effect() const
{
  return effect;
}

void Spell::set_modifier(const Modifier& new_modifier)
{
  modifier = new_modifier;
}

Modifier Spell::get_modifier() const
{
  return modifier;
}

void Spell::set_property(const string& key, const string& value)
{
  properties[key] = value;
}

bool Spell::has_property(const string& key) const
{
  auto p_it = properties.find(key);

  return (p_it != properties.end());
}

string Spell::get_property(const string& key) const
{
  string prop;

  auto p_it = properties.find(key);
  if (p_it != properties.end())
  {
    prop = p_it->second;
  }

  return prop;
}

#ifdef UNIT_TESTS
#include "unit_tests/Spell_test.cpp"
#endif
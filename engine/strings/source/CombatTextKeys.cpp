#include <sstream>
#include <boost/algorithm/string/replace.hpp>
#include "CombatTextKeys.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

// Strings for Combat
CombatTextKeys::CombatTextKeys()
{
}

string CombatTextKeys::get_close_miss_message(const bool is_player, const string& attacker, const string& miss_target)
{
  string close_miss_msg;
  
  if (is_player)
  {
    close_miss_msg = StringTable::get(CombatTextKeys::COMBAT_CLOSE_MISS_MESSAGE);
    boost::replace_first(close_miss_msg, "%s", miss_target);
  }
  else
  {
    close_miss_msg = StringTable::get(CombatTextKeys::COMBAT_CLOSE_MISS_MESSAGE_NP);
    boost::replace_first(close_miss_msg, "%s", attacker);
    boost::replace_first(close_miss_msg, "%s", miss_target);
    close_miss_msg[0] = toupper(close_miss_msg[0]);
  }
  
  return close_miss_msg;
}

string CombatTextKeys::get_miss_message(const bool is_player, const string& attacker, const string& miss_target)
{
  string miss_msg;

  if (is_player)
  {
    miss_msg = StringTable::get(CombatTextKeys::COMBAT_MISS_MESSAGE);
    boost::replace_first(miss_msg, "%s", miss_target);
  }
  else
  {
    miss_msg = StringTable::get(CombatTextKeys::COMBAT_MISS_MESSAGE_NP);
    boost::replace_first(miss_msg, "%s", attacker);
    boost::replace_first(miss_msg, "%s", miss_target);
    miss_msg[0] = toupper(miss_msg[0]);
  }
  
  return miss_msg;
}

string CombatTextKeys::get_critical_hit_message()
{
  string critical_hit_msg = StringTable::get(CombatTextKeys::COMBAT_CRITICAL_HIT_MESSAGE);
  return critical_hit_msg;
}

string CombatTextKeys::get_mighty_blow_message()
{
  string mighty_blow_msg = StringTable::get(CombatTextKeys::COMBAT_MIGHTY_BLOW_MESSAGE);
  return mighty_blow_msg;
}

string CombatTextKeys::get_hit_message(const bool is_player, const DamageType damage_type, const string& attacker, const string& hit_target)
{
  if (combat_damage_hit_messages.empty())
  {
    populate_combat_messages();
  }
  
  string key = create_key(is_player, damage_type);
  string hit_msg_sid = combat_damage_hit_messages[key];
  string hit_msg = StringTable::get(hit_msg_sid);
  
  // Now that we have the string, do the replacement(s) as necessary.
  if (is_player)
  {
    boost::replace_first(hit_msg, "%s", hit_target);
  }
  else
  {
    boost::replace_first(hit_msg, "%s", attacker);
    boost::replace_first(hit_msg, "%s", hit_target);
    hit_msg[0] = toupper(hit_msg[0]);
  }
  
  return hit_msg;
}

string CombatTextKeys::get_monster_death_message(const std::string& monster_name)
{
  string death_message = StringTable::get(CombatTextKeys::COMBAT_MONSTER_DEATH_MESSAGE);
  boost::replace_first(death_message, "%s", monster_name);
  death_message[0] = toupper(death_message[0]);
  return death_message;
}

string CombatTextKeys::get_no_damage_message(const bool is_player, const string& target)
{
  string no_damage_message;
  
  if (is_player)
  {
    no_damage_message = StringTable::get(CombatTextKeys::COMBAT_PLAYER_NO_DAMAGE_RECEIVED_MESSAGE);
    boost::replace_first(no_damage_message, "%s", StringTable::get(TextKeys::YOU));
  }
  else
  {
    no_damage_message = StringTable::get(CombatTextKeys::COMBAT_MONSTER_NO_DAMAGE_RECEIVED_MESSAGE);
    boost::replace_first(no_damage_message, "%s", target);
  }
  
  no_damage_message[0] = toupper(no_damage_message[0]);

  return no_damage_message;
}

string CombatTextKeys::get_ranged_attack_message(const bool is_player, const bool uses_launcher, const string& attacker, const string& ammunition, const string& target)
{
  string ranged_attack_message;
  bool has_target = !target.empty();
  
  if (is_player)
  {
    if (uses_launcher)
    {
      if (has_target)
      {
        ranged_attack_message = StringTable::get(CombatTextKeys::COMBAT_PLAYER_RANGED_ATTACK_LAUNCHER_MESSAGE);
      }
      else
      {
        ranged_attack_message = StringTable::get(CombatTextKeys::COMBAT_PLAYER_RANGED_ATTACK_LAUNCHER_NO_TARGET_MESSAGE);
      }
    }
    else
    {
      if (has_target)
      {
        ranged_attack_message = StringTable::get(CombatTextKeys::COMBAT_PLAYER_RANGED_ATTACK_MESSAGE);
      }
      else
      {
        ranged_attack_message = StringTable::get(CombatTextKeys::COMBAT_PLAYER_RANGED_ATTACK_NO_TARGET_MESSAGE);
      }
    }

    boost::replace_first(ranged_attack_message, "%s", StringTable::get(TextKeys::YOU));
    boost::replace_first(ranged_attack_message, "%s", ammunition);
    if (has_target) boost::replace_first(ranged_attack_message, "%s", target);
  }
  else
  {
    if (uses_launcher)
    {
      if (has_target)
      {
        ranged_attack_message = StringTable::get(CombatTextKeys::COMBAT_MONSTER_RANGED_ATTACK_LAUNCHER_MESSAGE);
      }
      else
      {
        ranged_attack_message = StringTable::get(CombatTextKeys::COMBAT_MONSTER_RANGED_ATTACK_LAUNCHER_NO_TARGET_MESSAGE);
      }
    }
    else
    {
      if (has_target)
      {
        ranged_attack_message = StringTable::get(CombatTextKeys::COMBAT_MONSTER_RANGED_ATTACK_MESSAGE);
      }
      else
      {
        ranged_attack_message = StringTable::get(CombatTextKeys::COMBAT_MONSTER_RANGED_ATTACK_NO_TARGET_MESSAGE);
      }
    }
    
    boost::replace_first(ranged_attack_message, "%s", attacker);
    boost::replace_first(ranged_attack_message, "%s", ammunition);
    if (has_target) boost::replace_first(ranged_attack_message, "%s", target);
  }
  
  ranged_attack_message[0] = toupper(ranged_attack_message[0]);
  return ranged_attack_message;
}

void CombatTextKeys::populate_combat_messages()
{
  combat_damage_hit_messages.insert(make_pair(create_key(0, DAMAGE_TYPE_SLASH), CombatTextKeys::COMBAT_HIT_SLASH_NP));
  combat_damage_hit_messages.insert(make_pair(create_key(1, DAMAGE_TYPE_SLASH), CombatTextKeys::COMBAT_HIT_SLASH));

  combat_damage_hit_messages.insert(make_pair(create_key(0, DAMAGE_TYPE_POUND), CombatTextKeys::COMBAT_HIT_POUND_NP));
  combat_damage_hit_messages.insert(make_pair(create_key(1, DAMAGE_TYPE_POUND), CombatTextKeys::COMBAT_HIT_POUND));

  combat_damage_hit_messages.insert(make_pair(create_key(0, DAMAGE_TYPE_PIERCE), CombatTextKeys::COMBAT_HIT_PIERCE_NP));
  combat_damage_hit_messages.insert(make_pair(create_key(1, DAMAGE_TYPE_PIERCE), CombatTextKeys::COMBAT_HIT_PIERCE));

  combat_damage_hit_messages.insert(make_pair(create_key(0, DAMAGE_TYPE_HEAT), CombatTextKeys::COMBAT_HIT_HEAT_NP));
  combat_damage_hit_messages.insert(make_pair(create_key(1, DAMAGE_TYPE_HEAT), CombatTextKeys::COMBAT_HIT_HEAT));

  combat_damage_hit_messages.insert(make_pair(create_key(0, DAMAGE_TYPE_COLD), CombatTextKeys::COMBAT_HIT_COLD_NP));
  combat_damage_hit_messages.insert(make_pair(create_key(1, DAMAGE_TYPE_COLD), CombatTextKeys::COMBAT_HIT_COLD));

  combat_damage_hit_messages.insert(make_pair(create_key(0, DAMAGE_TYPE_ACID), CombatTextKeys::COMBAT_HIT_ACID_NP));
  combat_damage_hit_messages.insert(make_pair(create_key(1, DAMAGE_TYPE_ACID), CombatTextKeys::COMBAT_HIT_ACID));

  combat_damage_hit_messages.insert(make_pair(create_key(0, DAMAGE_TYPE_POISON), CombatTextKeys::COMBAT_HIT_POISON_NP));
  combat_damage_hit_messages.insert(make_pair(create_key(1, DAMAGE_TYPE_POISON), CombatTextKeys::COMBAT_HIT_POISON));

  combat_damage_hit_messages.insert(make_pair(create_key(0, DAMAGE_TYPE_HOLY), CombatTextKeys::COMBAT_HIT_HOLY_NP));
  combat_damage_hit_messages.insert(make_pair(create_key(1, DAMAGE_TYPE_HOLY), CombatTextKeys::COMBAT_HIT_HOLY));

  combat_damage_hit_messages.insert(make_pair(create_key(0, DAMAGE_TYPE_SHADOW), CombatTextKeys::COMBAT_HIT_SHADOW_NP));
  combat_damage_hit_messages.insert(make_pair(create_key(1, DAMAGE_TYPE_SHADOW), CombatTextKeys::COMBAT_HIT_SHADOW));

  combat_damage_hit_messages.insert(make_pair(create_key(0, DAMAGE_TYPE_ARCANE), CombatTextKeys::COMBAT_HIT_ARCANE_NP));
  combat_damage_hit_messages.insert(make_pair(create_key(1, DAMAGE_TYPE_ARCANE), CombatTextKeys::COMBAT_HIT_ARCANE));

  combat_damage_hit_messages.insert(make_pair(create_key(0, DAMAGE_TYPE_LIGHTNING), CombatTextKeys::COMBAT_HIT_LIGHTNING_NP));
  combat_damage_hit_messages.insert(make_pair(create_key(1, DAMAGE_TYPE_LIGHTNING), CombatTextKeys::COMBAT_HIT_LIGHTNING));
}

string CombatTextKeys::create_key(const bool is_player, const DamageType damage_type)
{
  ostringstream ss;
  ss << is_player << ":" << damage_type;
  return ss.str();
}

const string CombatTextKeys::COMBAT_TARGET_TOO_FAR_AWAY = "COMBAT_TARGET_TOO_FAR_AWAY";
const string CombatTextKeys::COMBAT_PLAYER_RANGED_ATTACK_MESSAGE = "COMBAT_PLAYER_RANGED_ATTACK_MESSAGE";
const string CombatTextKeys::COMBAT_MONSTER_RANGED_ATTACK_MESSAGE = "COMBAT_MONSTER_RANGED_ATTACK_MESSAGE";
const string CombatTextKeys::COMBAT_PLAYER_RANGED_ATTACK_LAUNCHER_MESSAGE = "COMBAT_PLAYER_RANGED_ATTACK_LAUNCHER_MESSAGE";
const string CombatTextKeys::COMBAT_MONSTER_RANGED_ATTACK_LAUNCHER_MESSAGE = "COMBAT_MONSTER_RANGED_ATTACK_LAUNCHER_MESSAGE";
const string CombatTextKeys::COMBAT_PLAYER_RANGED_ATTACK_NO_TARGET_MESSAGE = "COMBAT_PLAYER_RANGED_ATTACK_NO_TARGET_MESSAGE";
const string CombatTextKeys::COMBAT_MONSTER_RANGED_ATTACK_NO_TARGET_MESSAGE = "COMBAT_MONSTER_RANGED_ATTACK_NO_TARGET_MESSAGE";
const string CombatTextKeys::COMBAT_PLAYER_RANGED_ATTACK_LAUNCHER_NO_TARGET_MESSAGE = "COMBAT_PLAYER_RANGED_ATTACK_LAUNCHER_NO_TARGET_MESSAGE";
const string CombatTextKeys::COMBAT_MONSTER_RANGED_ATTACK_LAUNCHER_NO_TARGET_MESSAGE = "COMBAT_MONSTER_RANGED_ATTACK_LAUNCHER_NO_TARGET_MESSAGE";
const string CombatTextKeys::COMBAT_PLAYER_NO_DAMAGE_RECEIVED_MESSAGE  = "COMBAT_PLAYER_NO_DAMAGE_RECEIVED_MESSAGE";
const string CombatTextKeys::COMBAT_MONSTER_NO_DAMAGE_RECEIVED_MESSAGE = "COMBAT_MONSTER_NO_DAMAGE_RECEIVED_MESSAGE";
const string CombatTextKeys::COMBAT_MONSTER_DEATH_MESSAGE  = "COMBAT_MONSTER_DEATH_MESSAGE";
const string CombatTextKeys::COMBAT_CLOSE_MISS_MESSAGE     = "COMBAT_CLOSE_MISS_MESSAGE";
const string CombatTextKeys::COMBAT_CLOSE_MISS_MESSAGE_NP  = "COMBAT_CLOSE_MISS_MESSAGE_NP"; 
const string CombatTextKeys::COMBAT_MISS_MESSAGE           = "COMBAT_MISS_MESSAGE";
const string CombatTextKeys::COMBAT_MISS_MESSAGE_NP        = "COMBAT_MISS_MESSAGE_NP";
const string CombatTextKeys::COMBAT_CRITICAL_HIT_MESSAGE   = "COMBAT_CRITICAL_HIT_MESSAGE";
const string CombatTextKeys::COMBAT_MIGHTY_BLOW_MESSAGE    = "COMBAT_MIGHTY_BLOW_MESSAGE";
const string CombatTextKeys::COMBAT_HIT_SLASH              = "COMBAT_HIT_SLASH";
const string CombatTextKeys::COMBAT_HIT_SLASH_NP           = "COMBAT_HIT_SLASH_NP";
const string CombatTextKeys::COMBAT_HIT_POUND              = "COMBAT_HIT_POUND";
const string CombatTextKeys::COMBAT_HIT_POUND_NP           = "COMBAT_HIT_POUND_NP";
const string CombatTextKeys::COMBAT_HIT_PIERCE             = "COMBAT_HIT_PIERCE";
const string CombatTextKeys::COMBAT_HIT_PIERCE_NP          = "COMBAT_HIT_PIERCE_NP";
const string CombatTextKeys::COMBAT_HIT_HEAT               = "COMBAT_HIT_HEAT";
const string CombatTextKeys::COMBAT_HIT_HEAT_NP            = "COMBAT_HIT_HEAT_NP";
const string CombatTextKeys::COMBAT_HIT_COLD               = "COMBAT_HIT_COLD";
const string CombatTextKeys::COMBAT_HIT_COLD_NP            = "COMBAT_HIT_COLD_NP";
const string CombatTextKeys::COMBAT_HIT_ACID               = "COMBAT_HIT_ACID";
const string CombatTextKeys::COMBAT_HIT_ACID_NP            = "COMBAT_HIT_ACID_NP";
const string CombatTextKeys::COMBAT_HIT_POISON             = "COMBAT_HIT_POISON";
const string CombatTextKeys::COMBAT_HIT_POISON_NP          = "COMBAT_HIT_POISON_NP";
const string CombatTextKeys::COMBAT_HIT_HOLY               = "COMBAT_HIT_HOLY";
const string CombatTextKeys::COMBAT_HIT_HOLY_NP            = "COMBAT_HIT_HOLY_NP";
const string CombatTextKeys::COMBAT_HIT_SHADOW             = "COMBAT_HIT_SHADOW";
const string CombatTextKeys::COMBAT_HIT_SHADOW_NP          = "COMBAT_HIT_SHADOW_NP";
const string CombatTextKeys::COMBAT_HIT_ARCANE             = "COMBAT_HIT_ARCANE";
const string CombatTextKeys::COMBAT_HIT_ARCANE_NP          = "COMBAT_HIT_ARCANE_NP";
const string CombatTextKeys::COMBAT_HIT_LIGHTNING          = "COMBAT_HIT_LIGHTNING";
const string CombatTextKeys::COMBAT_HIT_LIGHTNING_NP       = "COMBAT_HIT_LIGHTNING_NP";

map<string, string> CombatTextKeys::combat_damage_hit_messages;

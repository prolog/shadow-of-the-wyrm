#include <sstream>
#include <boost/algorithm/string/replace.hpp>
#include "CombatTextKeys.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "RNG.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

// Strings for Combat
CombatTextKeys::CombatTextKeys()
{
}

pair<string, string> CombatTextKeys::get_appropriate_attacker_and_target(const bool attacker_is_player, const bool attacked_is_player, const string& non_blind_attacker, const string& non_blind_target)
{
  pair<string, string> attacker_and_target(non_blind_attacker, non_blind_target);

  CurrentCreatureAbilities cca;

  if (!cca.can_see(Game::instance().get_current_player()))
  {
    // Attacker should be "something".  Target should be "something".
    // But only if the appropriate creature is not the player!
    if (!attacker_is_player)
    {
      attacker_and_target.first = StringTable::get(TextKeys::SOMETHING);
    }

    if (!attacked_is_player)
    {
      attacker_and_target.second = StringTable::get(TextKeys::SOMETHING);
    }
  }

  return attacker_and_target;
}

string CombatTextKeys::get_close_miss_message(const bool attacker_is_player, const bool attacked_is_player, const string& attacker, const string& miss_target)
{
  pair<string,string> attacker_and_target = get_appropriate_attacker_and_target(attacker_is_player, attacked_is_player, attacker, miss_target);
  string attack = attacker_and_target.first;
  string target = attacker_and_target.second;

  string close_miss_msg;
  
  if (attacker_is_player)
  {
    close_miss_msg = StringTable::get(CombatTextKeys::COMBAT_CLOSE_MISS_MESSAGE);
    boost::replace_first(close_miss_msg, "%s", target);
  }
  else
  {
    close_miss_msg = StringTable::get(CombatTextKeys::COMBAT_CLOSE_MISS_MESSAGE_NP);
    boost::replace_first(close_miss_msg, "%s", attack);
    boost::replace_first(close_miss_msg, "%s", target);
    close_miss_msg[0] = toupper(close_miss_msg[0]);
  }
  
  return close_miss_msg;
}

string CombatTextKeys::get_pierce_message(const bool attacker_is_player, const bool attacked_is_player, const string& attacker, const string& target)
{
  pair<string, string> attacker_and_target = get_appropriate_attacker_and_target(attacker_is_player, attacked_is_player, attacker, target);
  string app_attack = attacker_and_target.first;
  string app_target = attacker_and_target.second;

  string pierce_msg = StringTable::get(CombatTextKeys::COMBAT_PIERCE_MESSAGE_NP);

  if (attacked_is_player)
  {
    pierce_msg = StringTable::get(CombatTextKeys::COMBAT_PIERCE_MESSAGE);
  }

  boost::replace_first(pierce_msg, "%s", app_target);
  pierce_msg[0] = toupper(pierce_msg[0]);

  return pierce_msg;
}

string CombatTextKeys::get_vorpal_message(const bool attacker_is_player, const bool attacked_is_player, const string& attacker, const string& target)
{
  pair<string, string> attacker_and_target = get_appropriate_attacker_and_target(attacker_is_player, attacked_is_player, attacker, target);
  string app_attack = attacker_and_target.first;
  string app_target = attacker_and_target.second;

  string vorpal_msg = StringTable::get(CombatTextKeys::COMBAT_VORPAL_MESSAGE_NP);

  if (attacked_is_player)
  {
    vorpal_msg = StringTable::get(CombatTextKeys::COMBAT_VORPAL_MESSAGE);
  }

  boost::replace_first(vorpal_msg, "%s", app_target);
  vorpal_msg[0] = toupper(vorpal_msg[0]);

  return vorpal_msg;
}

string CombatTextKeys::get_explosive_message(const bool attacker_is_player, const bool attacked_is_player, const string& attacker, const string& target)
{
  pair<string, string> attacker_and_target = get_appropriate_attacker_and_target(attacker_is_player, attacked_is_player, attacker, target);
  string app_attack = attacker_and_target.first;
  string app_target = attacker_and_target.second;

  string explosive_msg = StringTable::get(CombatTextKeys::COMBAT_EXPLOSIVE_MESSAGE_NP);

  if (attacked_is_player)
  {
    explosive_msg = StringTable::get(CombatTextKeys::COMBAT_EXPLOSIVE_MESSAGE);
  }

  boost::replace_first(explosive_msg, "%s", app_target);
  explosive_msg[0] = toupper(explosive_msg[0]);

  return explosive_msg;
}

string CombatTextKeys::get_drain_message(const bool attacker_is_player, const bool attacked_is_player, const string& attacker, const string& target)
{
  pair<string, string> attacker_and_target = get_appropriate_attacker_and_target(attacker_is_player, attacked_is_player, attacker, target);
  string app_attack = attacker_and_target.first;
  string app_target = attacker_and_target.second;

  string drain_msg = StringTable::get(CombatTextKeys::COMBAT_DRAIN_MESSAGE_NP);

  if (attacked_is_player)
  {
    drain_msg = StringTable::get(CombatTextKeys::COMBAT_DRAIN_MESSAGE);
  }

  boost::replace_first(drain_msg, "%s", app_target);
  drain_msg[0] = toupper(drain_msg[0]);

  return drain_msg;
}

string CombatTextKeys::get_ethereal_message(const bool attacker_is_player, const bool attacked_is_player, const string& attacker, const string& target)
{
  pair<string, string> attacker_and_target = get_appropriate_attacker_and_target(attacker_is_player, attacked_is_player, attacker, target);
  string app_attack = attacker_and_target.first;
  string app_target = attacker_and_target.second;

  string ethereal_msg = StringTable::get(CombatTextKeys::COMBAT_ETHEREAL_MESSAGE_NP);

  if (attacked_is_player)
  {
    ethereal_msg = StringTable::get(CombatTextKeys::COMBAT_ETHEREAL_MESSAGE);
  }

  boost::replace_first(ethereal_msg, "%s", app_target);
  ethereal_msg[0] = toupper(ethereal_msg[0]);

  return ethereal_msg;
}

string CombatTextKeys::get_incorporeal_attack_message(const bool attacker_is_player, const bool attacked_is_player, const string& attacker, const string& target)
{
  pair<string, string> attacker_and_target = get_appropriate_attacker_and_target(attacker_is_player, attacked_is_player, attacker, target);
  string app_attack = attacker_and_target.first;
  string app_target = attacker_and_target.second;

  string incorp_msg = StringTable::get(CombatTextKeys::COMBAT_INCORPOREAL_MESSAGE_NP);

  if (attacked_is_player)
  {
    incorp_msg = StringTable::get(CombatTextKeys::COMBAT_INCORPOREAL_MESSAGE);
  }

  boost::replace_first(incorp_msg, "%s", app_target);
  incorp_msg[0] = toupper(incorp_msg[0]);

  return incorp_msg;
}

string CombatTextKeys::get_counter_message(const bool is_player, const string& desc)
{
  string counter_message = StringTable::get(COMBAT_COUNTER_MESSAGE);
  auto counter = get_appropriate_attacker_and_target(is_player, is_player, desc, desc);

  if (!is_player)
  {
    counter_message = StringTable::get(COMBAT_COUNTER_MESSAGE_NP);
    boost::replace_first(counter_message, "%s", counter.first);
  }

  counter_message[0] = toupper(counter_message[0]);
  return counter_message;
}

string CombatTextKeys::get_scything_message(const bool is_player, const string& attacker)
{
  string scything_message = StringTable::get(COMBAT_SCYTHING_MESSAGE);
  auto scything = get_appropriate_attacker_and_target(is_player, is_player, attacker, attacker);

  if (!is_player)
  {
    scything_message = StringTable::get(COMBAT_SCYTHING_MESSAGE_NP);
    boost::replace_first(scything_message, "%s", scything.first);
  }

  scything_message[0] = toupper(scything_message[0]);
  return scything_message;
}

string CombatTextKeys::get_miss_message(const bool attacker_is_player, const bool attacked_is_player, const string& attacker, const string& miss_target)
{
  pair<string,string> attacker_and_target = get_appropriate_attacker_and_target(attacker_is_player, attacked_is_player, attacker, miss_target);
  string attack = attacker_and_target.first;
  string target = attacker_and_target.second;

  string miss_msg;

  if (attacker_is_player)
  {
    miss_msg = StringTable::get(CombatTextKeys::COMBAT_MISS_MESSAGE);
    boost::replace_first(miss_msg, "%s", target);
  }
  else
  {
    miss_msg = StringTable::get(CombatTextKeys::COMBAT_MISS_MESSAGE_NP);
    boost::replace_first(miss_msg, "%s", attack);
    boost::replace_first(miss_msg, "%s", target);
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

string CombatTextKeys::get_hit_message(const bool attacker_is_player, const bool attacked_is_player, const DamageType damage_type, const string& attacker, const string& hit_target, const bool use_multiple_damage_type_msgs)
{
  pair<string,string> attacker_and_target = get_appropriate_attacker_and_target(attacker_is_player, attacked_is_player, attacker, hit_target);
  string attack = attacker_and_target.first;
  string target = attacker_and_target.second;

  if (combat_damage_hit_messages.empty())
  {
    populate_combat_messages();
  }
  
  string key = create_key(attacker_is_player, damage_type);
  vector<string> hit_msg_v = combat_damage_hit_messages[key];
  string hit_msg_sid;
  string hit_msg;

  if (!hit_msg_v.empty())
  {
    int idx = 0;

    if (use_multiple_damage_type_msgs)
    {
      idx = RNG::range(0, hit_msg_v.size() - 1);
    }

    hit_msg_sid = hit_msg_v.at(idx);
    hit_msg = StringTable::get(hit_msg_sid);
  }
  
  // Now that we have the string, do the replacement(s) as necessary.
  if (attacker_is_player)
  {
    boost::replace_first(hit_msg, "%s", target);
  }
  else
  {
    boost::replace_first(hit_msg, "%s", attack);
    boost::replace_first(hit_msg, "%s", target);
    hit_msg[0] = toupper(hit_msg[0]);
  }
  
  return hit_msg;
}

string CombatTextKeys::get_monster_killed_message(const std::string& monster_name)
{
  CurrentCreatureAbilities cca;

  string death_message = StringTable::get(CombatTextKeys::COMBAT_MONSTER_KILLED_MESSAGE);
  boost::replace_first(death_message, "%s", monster_name);

  if (!cca.can_see(Game::instance().get_current_player()))
  {
    death_message = StringTable::get(CombatTextKeys::COMBAT_MONSTER_KILLED_OR_DIES_MESSAGE_PLAYER_BLIND);
  }

  death_message[0] = toupper(death_message[0]);
  return death_message;
}

string CombatTextKeys::get_monster_dies_message(const std::string& monster_name)
{
  CurrentCreatureAbilities cca;

  string death_message = StringTable::get(CombatTextKeys::COMBAT_MONSTER_DIES_MESSAGE);
  boost::replace_first(death_message, "%s", monster_name);

  if (!cca.can_see(Game::instance().get_current_player()))
  {
    death_message = StringTable::get(CombatTextKeys::COMBAT_MONSTER_KILLED_OR_DIES_MESSAGE_PLAYER_BLIND);
  }

  death_message[0] = toupper(death_message[0]);
  return death_message;
}

string CombatTextKeys::get_no_damage_message(const bool target_is_player, const string& non_blind_target)
{
  string no_attacker;
  pair<string,string> attacker_and_target = get_appropriate_attacker_and_target(false, target_is_player, no_attacker, non_blind_target);
  string target = attacker_and_target.second;

  string no_damage_message;
  
  if (target_is_player)
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

string CombatTextKeys::get_ranged_attack_message(const bool attacker_is_player, const bool attacked_is_player, const bool uses_launcher, const string& non_blind_attacker, const string& ammunition, const string& non_blind_target)
{
  pair<string,string> attacker_and_target = get_appropriate_attacker_and_target(attacker_is_player, attacked_is_player, non_blind_attacker, non_blind_target);
  string attacker = attacker_and_target.first;
  string target = attacker_and_target.second;

  string ranged_attack_message;
  bool has_target = !target.empty();
  
  if (attacker_is_player)
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

string CombatTextKeys::get_split_message(const string& split_creature)
{
  string split_msg = StringTable::get(COMBAT_SPLIT_MESSAGE);
  boost::replace_first(split_msg, "%s", split_creature);
  split_msg[0] = toupper(split_msg[0]);

  return split_msg;
}

void CombatTextKeys::populate_combat_messages()
{
  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(0, DamageType::DAMAGE_TYPE_SLASH), {"COMBAT_HIT_SLASH_NP", "COMBAT_HIT_SLASH2_NP"}));
  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(1, DamageType::DAMAGE_TYPE_SLASH), {"COMBAT_HIT_SLASH", "COMBAT_HIT_SLASH2"}));

  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(0, DamageType::DAMAGE_TYPE_POUND), {"COMBAT_HIT_POUND_NP", "COMBAT_HIT_POUND2_NP" }));
  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(1, DamageType::DAMAGE_TYPE_POUND), {"COMBAT_HIT_POUND", "COMBAT_HIT_POUND2" }));

  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(0, DamageType::DAMAGE_TYPE_PIERCE), {"COMBAT_HIT_PIERCE_NP", "COMBAT_HIT_PIERCE2_NP" }));
  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(1, DamageType::DAMAGE_TYPE_PIERCE), {"COMBAT_HIT_PIERCE", "COMBAT_HIT_PIERCE2" }));

  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(0, DamageType::DAMAGE_TYPE_HEAT), {"COMBAT_HIT_HEAT_NP", "COMBAT_HIT_HEAT2_NP" }));
  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(1, DamageType::DAMAGE_TYPE_HEAT), {"COMBAT_HIT_HEAT", "COMBAT_HIT_HEAT2" }));

  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(0, DamageType::DAMAGE_TYPE_COLD), {"COMBAT_HIT_COLD_NP", "COMBAT_HIT_COLD2_NP" }));
  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(1, DamageType::DAMAGE_TYPE_COLD), {"COMBAT_HIT_COLD", "COMBAT_HIT_COLD2" }));

  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(0, DamageType::DAMAGE_TYPE_ACID), {"COMBAT_HIT_ACID_NP", "COMBAT_HIT_ACID2_NP" }));
  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(1, DamageType::DAMAGE_TYPE_ACID), {"COMBAT_HIT_ACID", "COMBAT_HIT_ACID2" }));

  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(0, DamageType::DAMAGE_TYPE_POISON), {"COMBAT_HIT_POISON_NP", "COMBAT_HIT_POISON2_NP" }));
  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(1, DamageType::DAMAGE_TYPE_POISON), {"COMBAT_HIT_POISON", "COMBAT_HIT_POISON2" }));

  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(0, DamageType::DAMAGE_TYPE_HOLY), {"COMBAT_HIT_HOLY_NP", "COMBAT_HIT_HOLY2_NP" }));
  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(1, DamageType::DAMAGE_TYPE_HOLY), {"COMBAT_HIT_HOLY", "COMBAT_HIT_HOLY2" }));

  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(0, DamageType::DAMAGE_TYPE_SHADOW), {"COMBAT_HIT_SHADOW_NP", "COMBAT_HIT_SHADOW2_NP" }));
  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(1, DamageType::DAMAGE_TYPE_SHADOW), {"COMBAT_HIT_SHADOW", "COMBAT_HIT_SHADOW2" }));

  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(0, DamageType::DAMAGE_TYPE_ARCANE), {"COMBAT_HIT_ARCANE_NP", "COMBAT_HIT_ARCANE2_NP" }));
  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(1, DamageType::DAMAGE_TYPE_ARCANE), {"COMBAT_HIT_ARCANE", "COMBAT_HIT_ARCANE2" }));

  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(0, DamageType::DAMAGE_TYPE_LIGHTNING), {"COMBAT_HIT_LIGHTNING_NP", "COMBAT_HIT_LIGHTNING2_NP" }));
  combat_damage_hit_messages.insert(make_pair<string, vector<string>>(create_key(1, DamageType::DAMAGE_TYPE_LIGHTNING), {"COMBAT_HIT_LIGHTNING", "COMBAT_HIT_LIGHTNING2"}));
}

string CombatTextKeys::create_key(const bool is_player, const DamageType damage_type)
{
  ostringstream ss;
  ss << is_player << ":" << static_cast<int>(damage_type);
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
const string CombatTextKeys::COMBAT_MONSTER_KILLED_MESSAGE = "COMBAT_MONSTER_KILLED_MESSAGE";
const string CombatTextKeys::COMBAT_MONSTER_DIES_MESSAGE   = "COMBAT_MONSTER_DIES_MESSAGE";
const string CombatTextKeys::COMBAT_MONSTER_KILLED_OR_DIES_MESSAGE_PLAYER_BLIND = "COMBAT_MONSTER_KILLED_OR_DIES_MESSAGE_PLAYER_BLIND";
const string CombatTextKeys::COMBAT_CLOSE_MISS_MESSAGE     = "COMBAT_CLOSE_MISS_MESSAGE";
const string CombatTextKeys::COMBAT_CLOSE_MISS_MESSAGE_NP  = "COMBAT_CLOSE_MISS_MESSAGE_NP"; 
const string CombatTextKeys::COMBAT_PIERCE_MESSAGE         = "COMBAT_PIERCE_MESSAGE";
const string CombatTextKeys::COMBAT_PIERCE_MESSAGE_NP      = "COMBAT_PIERCE_MESSAGE_NP";
const string CombatTextKeys::COMBAT_VORPAL_MESSAGE         = "COMBAT_VORPAL_MESSAGE";
const string CombatTextKeys::COMBAT_VORPAL_MESSAGE_NP      = "COMBAT_VORPAL_MESSAGE_NP";
const string CombatTextKeys::COMBAT_EXPLOSIVE_MESSAGE      = "COMBAT_EXPLOSIVE_MESSAGE";
const string CombatTextKeys::COMBAT_EXPLOSIVE_MESSAGE_NP   = "COMBAT_EXPLOSIVE_MESSAGE_NP";
const string CombatTextKeys::COMBAT_DRAIN_MESSAGE          = "COMBAT_DRAIN_MESSAGE";
const string CombatTextKeys::COMBAT_DRAIN_MESSAGE_NP       = "COMBAT_DRAIN_MESSAGE_NP";
const string CombatTextKeys::COMBAT_ETHEREAL_MESSAGE       = "COMBAT_ETHEREAL_MESSAGE";
const string CombatTextKeys::COMBAT_ETHEREAL_MESSAGE_NP    = "COMBAT_ETHEREAL_MESSAGE_NP";
const string CombatTextKeys::COMBAT_INCORPOREAL_MESSAGE    = "COMBAT_INCORPOREAL_MESSAGE";
const string CombatTextKeys::COMBAT_INCORPOREAL_MESSAGE_NP = "COMBAT_INCORPOREAL_MESSAGE_NP";
const string CombatTextKeys::COMBAT_COUNTER_MESSAGE        = "COMBAT_COUNTER_MESSAGE";
const string CombatTextKeys::COMBAT_COUNTER_MESSAGE_NP     = "COMBAT_COUNTER_MESSAGE_NP";
const string CombatTextKeys::COMBAT_SCYTHING_MESSAGE       = "COMBAT_SCYTHING_MESSAGE";
const string CombatTextKeys::COMBAT_SCYTHING_MESSAGE_NP    = "COMBAT_SCYTHING_MESSAGE_NP";
const string CombatTextKeys::COMBAT_MISS_MESSAGE           = "COMBAT_MISS_MESSAGE";
const string CombatTextKeys::COMBAT_MISS_MESSAGE_NP        = "COMBAT_MISS_MESSAGE_NP";
const string CombatTextKeys::COMBAT_CRITICAL_HIT_MESSAGE   = "COMBAT_CRITICAL_HIT_MESSAGE";
const string CombatTextKeys::COMBAT_MIGHTY_BLOW_MESSAGE    = "COMBAT_MIGHTY_BLOW_MESSAGE";
const string CombatTextKeys::COMBAT_SPLIT_MESSAGE          = "COMBAT_SPLIT_MESSAGE";

map<string, vector<string>> CombatTextKeys::combat_damage_hit_messages;

#pragma once
#include <string>

class CreatureProperties
{
  public:
    static const std::string CREATURE_PROPERTIES_SPEECH_TEXT_SID;
    static const std::string CREATURE_PROPERTIES_LAST_BESTIARY_SEARCH;
    static const std::string CREATURE_PROPERTIES_LAST_ITEM_CODEX_SEARCH;
    static const std::string CREATURE_PROPERTIES_FOLLOWS_CR_ID; // used for summoned/bound creatures
    static const std::string CREATURE_PROPERTIES_AUTOMOVEMENT_COORDS_VISITED;
    static const std::string CREATURE_PROPERTIES_LEAVES_CORPSE;
    static const std::string CREATURE_PROPERTIES_LEAVES_EQUIPMENT;
    static const std::string CREATURE_PROPERTIES_ALLOWS_RANDOM_DROPS;
    static const std::string CREATURE_PROPERTIES_STOLEN_FROM;
    static const std::string CREATURE_PROPERTIES_PACIFIED;
    static const std::string CREATURE_PROPERTIES_WINNER;
    static const std::string CREATURE_PROPERTIES_IGNORE_RACIAL_MOVEMENT_RESTRICTIONS;
    static const std::string CREATURE_PROPERTIES_BACKSTABBED;
    static const std::string CREATURE_PROPERTIES_TELEPORTED;

    // FREE_HIDDEN_ACTIONS is a counter.  When set (defaults to 1), then
    // the next action will reveal the player.  Certain actions (e.g.
    // successful stealth) will increment this counter.  It is decremented
    // at the end of each turn when performing an action that has an
    // action cost.  This system allows sneaking to be modelled, while
    // remaining general enough to "free stealth actions" are possible
    // later on.
    static const std::string CREATURE_PROPERTIES_FREE_HIDDEN_ACTIONS;
    static const std::string CREATURE_PROPERTIES_FIRST_KILL_ID;
    static const std::string CREATURE_PROPERTIES_NO_EXP;
    static const std::string CREATURE_PROPERTIES_TAMED;
    static const std::string CREATURE_PROPERTIES_LEADER_ID;
    static const std::string CREATURE_PROPERTIES_FOLLOWER_PREFIX;
    static const std::string CREATURE_PROPERTIES_HIRELING_CHAT_SID;
    static const std::string CREATURE_PROPERTIES_HIRE_FEE;
    static const std::string CREATURE_PROPERTIES_HIRELINGS_HIRED;
    static const std::string CREATURE_PROPERTIES_ADVENTURERS_JOINED;
    static const std::string CREATURE_PROPERTIES_PRIMARY_MELEE_RANGE;
    static const std::string CREATURE_PROPERTIES_KILLED_BY_SOURCE;
    static const std::string CREATURE_PROPERTIES_KILLED_BY_DEPTH;
    static const std::string CREATURE_PROPERTIES_KILLED_BY_MAP;
    static const std::string CREATURE_PROPERTIES_SPELL_IN_PROGRESS;
    static const std::string CREATURE_PROPERTIES_ITEM_IN_USE;
    static const std::string CREATURE_PROPERTIES_NIGHT_SPEECH_TEXT_SID;
    static const std::string CREATURE_PROPERTIES_APOSTATE;
    static const std::string CREATURE_PROPERTIES_GAME_STARTED;
    static const std::string CREATURE_PROPERTIES_CHARACTER_STARTED;
    static const std::string CREATURE_PROPERTIES_GAME_DATE;
    static const std::string CREATURE_PROPERTIES_COWARD;
    static const std::string CREATURE_PROPERTIES_FLEEING;
    static const std::string CREATURE_PROPERTIES_MINER;
    static const std::string CREATURE_PROPERTIES_HIDING_COOLDOWN;

  protected:
    CreatureProperties();
    ~CreatureProperties();
};

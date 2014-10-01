#pragma once
#include <string>

// A class containing static text keys needed for the various command classes.
class CommandKeys
{
  public:
    static const std::string QUIT;
    static const std::string VERSION;
    static const std::string GAME_DATE_TIME;
    static const std::string MOVE_NORTHWEST;
    static const std::string MOVE_NORTH;
    static const std::string MOVE_NORTHEAST;
    static const std::string MOVE_WEST;
    static const std::string SEARCH; // search/idle is the same.
    static const std::string MOVE_EAST;
    static const std::string MOVE_SOUTHWEST;
    static const std::string MOVE_SOUTH;
    static const std::string MOVE_SOUTHEAST;
    static const std::string MOVE_UP;
    static const std::string MOVE_DOWN;
    static const std::string AUTOMATIC_MOVEMENT;
    static const std::string ATTACK_NORTHWEST;
    static const std::string ATTACK_NORTH;
    static const std::string ATTACK_NORTHEAST;
    static const std::string ATTACK_WEST;
    static const std::string ATTACK_EAST;
    static const std::string ATTACK_SOUTHWEST;
    static const std::string ATTACK_SOUTH;
    static const std::string ATTACK_SOUTHEAST;
    static const std::string PICK_UP_ITEM;
    static const std::string DROP_ITEM;
    static const std::string CHAR_DUMP;
    static const std::string INVENTORY;
    static const std::string PRAY;
    static const std::string MELEE_WEAPON_INFO;
    static const std::string RANGED_WEAPON_INFO;
    static const std::string SELECT_TILE; // aka "look" - this can be reused for general targetting code
    static const std::string FIRE_MISSILE;
    static const std::string QUAFF;
    static const std::string READ;
    static const std::string CHECK_CURRENCY;
    static const std::string SAVE_GAME;
    static const std::string EAT;
    static const std::string CHAT;
    static const std::string APPLY_FEATURE;
    static const std::string QUEST_LIST;
    static const std::string RELOAD_SCRIPTS_AND_SIDS;
    static const std::string RUN_SCRIPT;
    static const std::string CAST_SPELL;
    static const std::string BESTIARY;
    static const std::string EVOKE;
    static const std::string SHOW_RESISTANCES;
    static const std::string SHOW_CONDUCTS;
    static const std::string LATEST_MESSAGES;
    static const std::string KICK;
    static const std::string OFFER;

    // Helpful public functions
    static bool is_movement_type_key(const std::string& key);
    static bool is_attack_type_key(const std::string& key);

  protected:
    CommandKeys();
    ~CommandKeys();
};

#pragma once
#include <string>

// A class containing static text keys needed for the various command classes.
class CommandKeys
{
  public:
    static const std::string QUIT;
    static const std::string VERSION;
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

    // Helpful public functions
    static bool is_movement_type_key(const std::string& key);
    static bool is_attack_type_key(const std::string& key);

  protected:
    CommandKeys();
    ~CommandKeys();
};

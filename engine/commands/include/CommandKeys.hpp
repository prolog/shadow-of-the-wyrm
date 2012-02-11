#pragma once
#include <string>

// A class containing static text keys needed for the various command classes.
class CommandKeys
{
  public:
    static std::string QUIT;
    static std::string VERSION;
    static std::string MOVE_NORTHWEST;
    static std::string MOVE_NORTH;
    static std::string MOVE_NORTHEAST;
    static std::string MOVE_WEST;
    static std::string SEARCH; // search/idle is the same.
    static std::string MOVE_EAST;
    static std::string MOVE_SOUTHWEST;
    static std::string MOVE_SOUTH;
    static std::string MOVE_SOUTHEAST;
    static std::string MOVE_UP;
    static std::string MOVE_DOWN;
    static std::string PICK_UP_ITEM;
    static std::string DROP_ITEM;
    static std::string CHAR_DUMP;
    static std::string INVENTORY;

    // Helpful public functions
    static bool is_movement_type_key(const std::string& key);

  protected:
    CommandKeys();
    ~CommandKeys();
};

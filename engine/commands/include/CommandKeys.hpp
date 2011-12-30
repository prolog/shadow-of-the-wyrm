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

    // Helpful public functions
    static bool is_movement_type_key(const std::string& key);

  protected:
    CommandKeys();
    ~CommandKeys();
};

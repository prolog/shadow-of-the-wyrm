#pragma once
#include <string>
#include "Creature.hpp"

// Utility functions for creatures that are here (instead of on the
// Creature class) because they require engine-specific work, such as
// looking up strings, etc.
class CreatureUtils
{
  public:
    static std::string get_race_class_synopsis(CreaturePtr c);
    static void handle_alignment_change(CreaturePtr c, const int new_alignment);

    // Increment a statistic, adding a message if desired.
    static void incr_str(CreaturePtr c, const bool add_msg);
    static void incr_dex(CreaturePtr c, const bool add_msg);
    static void incr_agi(CreaturePtr c, const bool add_msg);
    static void incr_hea(CreaturePtr c, const bool add_msg);
    static void incr_int(CreaturePtr c, const bool add_msg);
    static void incr_wil(CreaturePtr c, const bool add_msg);
    static void incr_cha(CreaturePtr c, const bool add_msg);

  protected:
    CreatureUtils();
    ~CreatureUtils();
};


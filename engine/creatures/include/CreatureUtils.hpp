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

  protected:
    CreatureUtils();
    ~CreatureUtils();
};


#pragma once
#include <string>
#include "Creature.hpp"
#include "Race.hpp"
#include "Class.hpp"
#include "Deity.hpp"

// Utility functions for creatures that are here (instead of on the
// Creature class) because they require engine-specific work, such as
// looking up strings, etc.
class CreatureUtils
{
  public:
    static std::string get_race_class_synopsis(CreaturePtr c);

    static void handle_alignment_change(CreaturePtr c, const int new_alignment);

    static void add_hunger_level_message_if_necessary(CreaturePtr c, const int old_hunger, const int new_hunger);

    static RacePtr get_random_user_playable_race();
    static ClassPtr get_random_user_playable_class();
    static DeityPtr get_random_deity_for_race(RacePtr race);

    // Check to see if the given creature is either the player, or exists
    // on the player's view map.
    static bool is_player_or_in_los(CreaturePtr c);

    // Can the creature pick up the item?
    static bool can_pick_up(CreaturePtr c, ItemPtr i);

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

    static void initialize_hunger_message_sid_map();
    static std::map<HungerLevel, std::string> hunger_message_sid_map;
};


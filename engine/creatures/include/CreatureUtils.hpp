#pragma once
#include <string>
#include "Creature.hpp"
#include "CreatureStatusTypes.hpp"
#include "Race.hpp"
#include "Class.hpp"
#include "Deity.hpp"
#include "SpellTypes.hpp"
#include "Wearable.hpp"
#include "Weapon.hpp"

// Utility functions for creatures that are here (instead of on the
// Creature class) because they require engine-specific work, such as
// looking up strings, etc.
class CreatureUtils
{
  public:
    static std::string get_race_class_synopsis(CreaturePtr c);

    static void handle_alignment_change(CreaturePtr c, const int new_alignment);

    static void add_hunger_level_message_if_necessary(CreaturePtr c, const int old_hunger, const int new_hunger);

    static Race* get_random_user_playable_race();
    static Class* get_random_user_playable_class();
    static Deity* get_random_deity_for_race(Race* race);

    // Check to see if the given creature is either the player, or exists
    // on the player's view map.
    static bool is_player_or_in_los(CreaturePtr c);

    // Can the creature pick up the item?
    static std::tuple<bool, uint, std::string> can_pick_up(CreaturePtr c, ItemPtr i);

    // Can the creature equip the weapon?
    static bool can_equip_weapon(CreaturePtr creature, WeaponPtr weapon);

    // Increment a statistic, adding a message if desired.
    static void incr_str(CreaturePtr c, const bool add_msg);
    static void incr_dex(CreaturePtr c, const bool add_msg);
    static void incr_agi(CreaturePtr c, const bool add_msg);
    static void incr_hea(CreaturePtr c, const bool add_msg);
    static void incr_int(CreaturePtr c, const bool add_msg);
    static void incr_wil(CreaturePtr c, const bool add_msg);
    static void incr_cha(CreaturePtr c, const bool add_msg);

    // Check to see if any of the creatures in a particular threat map exist
    // in the given map.
    static bool threat_exists_in_map(const ThreatMap& tm, MapPtr map);

    static bool has_spell_for_situation_type(CreaturePtr creature, const SpellSituationType sst);

    // Mark modifiers older than a certain time, or by spell/status.
    static void mark_modifiers_for_deletion(CreaturePtr creature, const double seconds, const double min_expiry = 0.0, const StatusRemovalType sr = StatusRemovalType::STATUS_REMOVAL_FINALIZE);
    static void mark_modifiers_for_deletion(CreaturePtr creature, const std::string& identifier, const StatusRemovalType sr);

    // Remove any marked modifiers
    static void remove_modifiers(CreaturePtr creature);
    static void process_creature_modifiers(CreaturePtr creature, std::vector<std::pair<std::string, Modifier>>& modifiers, const StatusRemovalType sr);
    static void process_creature_modifier(CreaturePtr creature, std::pair<std::string, Modifier>& modifier, const StatusRemovalType sr, const std::string& item_id = "");

    // Apply/remove status ailments from the wearable to the creature
    static void apply_status_ailments(WearablePtr wearable, CreaturePtr creature);
    static void remove_status_ailments_from_wearable(WearablePtr wearable, CreaturePtr creature);
    static bool has_status_ailment_from_wearable(CreaturePtr creature, const std::string& status_id);

    static MapPtr update_fov_map(MapPtr current_map, MapPtr view_map, CreaturePtr creature);

    static bool has_negative_status(CreaturePtr creature);

    // Returns the number of times str was incremented
    static int adjust_str_until_unburdened(CreaturePtr creature);

    static CreatureMap get_followers(CreaturePtr creature, MapPtr map);
    static CreatureMap get_followers_in_fov(CreaturePtr creature);
    static std::string get_follower_property_prefix();

    static bool remove_negative_statuses_from_creature(CreaturePtr creature);

    static bool has_skill_for_spell(CreaturePtr creature, const std::string& spell_id);

    static std::string get_description_for_fov_message(CreaturePtr player, CreaturePtr creature_to_describe);

    static CreatureSize get_size(CreaturePtr creature);

    static void set_leadership(CreaturePtr creature, const std::string& leader_id, MapPtr map, const int pass = 1);

    static bool has_primordial_essence(CreaturePtr creature);

    static void add_piety_message_if_player(CreaturePtr creature);

  protected:
    CreatureUtils();
    ~CreatureUtils();

    static void add_removal_message(CreaturePtr creature, const std::string& spell_id);

    static void initialize_hunger_maps();
    static std::map<HungerLevel, std::string> hunger_message_sid_map;
    static std::map<HungerLevel, Colour> hunger_colour_map;

    static const int LEADERSHIP_MAX_PASSES;
};

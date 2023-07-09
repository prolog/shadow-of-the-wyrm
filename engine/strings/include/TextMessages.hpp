#pragma once
#include <string>
#include "Creature.hpp"
#include "CreatureFeatures.hpp"
#include "Deity.hpp"
#include "EquipmentTypes.hpp"
#include "Item.hpp"
#include "tiles.hpp"
#include "Spell.hpp"
#include "StartingLocation.hpp"

class TextMessages
{
  public:
    static std::string get_full_header_text(const std::string& header, const uint num_cols);
    static std::string get_welcome_message(const std::string& player_name, const bool new_player);
    static std::string get_death_message(const std::string& deity_death_message_sid);
    static std::string get_player_description(const std::string& player_name);
    static std::string get_npc_escapes_message(const std::string& creature_description);
    static std::string get_npc_flees_message(const std::string& creature_description);
    static std::string get_npc_turns_to_fight_message(const std::string& creature_description);
    static std::string get_npc_level_message(const std::string& creature_description);
    static std::string get_action_not_found_message(const std::string& command_action);
    static std::string get_dumping_character_message(const std::string& char_name, const std::string& dir);
    static std::string get_sex(const CreatureSex sex);
    static std::string get_sex_abrv(const CreatureSex sex);
    static std::string get_name_and_title(CreaturePtr creature);
    static std::string get_carrying_capacity_message(CreaturePtr creature);
    static std::string get_equipment_location(const EquipmentWornLocation location);
    static std::string get_confirmation_message(const std::string& query_or_sid);
    static std::string get_area_entrance_message_given_terrain_type(const TileType type);
    static std::string get_item_drop_message(CreaturePtr creature, const bool blind, ItemPtr item);
    static std::string get_burial_message(CreaturePtr creature);
    static std::string get_item_pick_up_message(const bool player_blind, CreaturePtr creature, ItemPtr item);
    static std::string get_item_pick_up_and_merge_message(const bool player_blind, CreaturePtr creature, ItemPtr item);
    static std::string get_item_on_ground_description_message(const bool blind, ItemPtr item);
    static std::string get_currency_amount_message(const uint currency_amount);
    static std::string get_unpaid_amount_message(const uint unpaid_amount);
    static std::string get_reflexive_pronoun(CreaturePtr creature);
    static std::string get_experience_synopsis(const int level, const int exp, const int exp_required, const int next_level, const std::string& race_name, const float r_mult, const std::string class_name, const float c_mult);
    static std::string get_special_day_message(const std::string& day_name_sid, const std::string& day_desc_sid);
    static std::string get_engraving_message(const std::string& engraving_sid);
    static std::string get_inscription_message(const std::string& inscription_sid, const bool is_world_map);
    static std::string get_replacement_message(const std::string& message, const std::string& replace);
    static std::string get_bool_sid(const bool val);
    static std::string get_character_creation_synopsis(const CreatureSex cs, Race* race, Class* cur_class, const std::string& deity_id, StartingLocation* sl);
    static std::string get_slot_machine_message(const int cost, const int pct_chance_win, const int payout_amount);
    static std::string get_slot_machine_outcome_message(const std::string& first_sid, const std::string& second_sid, const std::string& third_sid);
    static std::string get_damage_message(const Damage& damage);
    static std::string get_equip_message(const std::string& creature_desc_sid, const std::string& item_desc);
    static std::string get_hirelings_hired_message(const int hirelings_hired);
    static std::string get_adventurers_joined_message(const int adv_joined);
    static std::string get_modifier_message(const std::string& status_or_spell_id, const Modifier& m, CreaturePtr c);
    static std::string get_ending_message(const std::string& ending_time);
    static std::string get_killed_by_message(const std::string& killed_by_source);
    static std::string get_death_depth_location_message(const std::string& depth, const std::string& location);
    static std::string get_build_message(const std::string& thing_built);
    static std::string get_select_age_message(const int min_age, const int max_age);
    static std::string get_and_replace(const std::string& message_sid, const std::vector<std::string>& replacements);
    static std::string get_hidden_treasure_message(const bool is_underwater);
    static std::string get_buried_treasure_message();
    static std::string get_shipwreck_message();

  protected:
    TextMessages();
    ~TextMessages();

    static const std::string WELCOME_MESSAGE;
    static const std::string WELCOME_BACK_MESSAGE;
    static const std::string DUMPING_CHARACTER_MESSAGE;
    static const std::string ITEM_DROP_MESSAGE;
    static const std::string ITEM_DROP_MESSAGE_MONSTER;
    static const std::string BURY_MESSAGE;
    static const std::string BURY_MESSAGE_MONSTER;
    static const std::string ITEM_PICK_UP_MESSAGE_PLAYER;
    static const std::string ITEM_PICK_UP_MESSAGE_MONSTER;
    static const std::string ITEM_PICK_UP_AND_MERGE_MESSAGE_PLAYER;
    static const std::string ITEM_PICK_UP_AND_MERGE_MESSAGE_MONSTER;
    static const std::string ITEM_ON_GROUND_BLIND_DESCRIPTION_MESSAGE;
    static const std::string ITEM_ON_GROUND_DESCRIPTION_MESSAGE;
    static const std::string CURRENCY_MESSAGE_SINGLE;
    static const std::string CURRENCY_MESSAGE_MULTIPLE;
    static const std::string CURRENCY_OWING_MESSAGE;
    static const std::string NAME_TITLE_MESSAGE;
    static const std::string EXPERIENCE_SYNOPSIS_MESSAGE;
    static const std::string EXPERIENCE_SYNOPSIS_MAX_MESSAGE;
    static const std::string SPECIAL_DAY_MESSAGE;
    static const std::string ENGRAVING_MESSAGE;
    static const std::string INSCRIPTION_MESSAGE;
    static const std::string INSCRIPTION_WORLD_MESSAGE;
    static const std::string SLOT_MACHINE_MESSAGE;
    static const std::string SLOT_MACHINE_OUTCOME_MESSAGE;
    static const std::string CARRYING_CAPACITY_MESSAGE;
    static const std::string DAMAGE_MESSAGE;
    static const std::string NPC_LEVEL_MESSAGE;
    static const std::string NPC_EQUIP_MESSAGE;
    static const std::string HIRELINGS_HIRED_MESSAGE;
    static const std::string ADVENTURERS_JOINED_MESSAGE;
    static const std::string AFFECTED_BY;
    static const std::string ENDING_MESSAGE;
    static const std::string KILLED_BY_MESSAGE;
    static const std::string DEATH_DEPTH_LOCATION_MESSAGE;
    static const std::string BUILD_MESSAGE;
    static const std::string SELECT_AGE_MESSAGE;
    static const std::string BURIED_TREASURE_MESSAGE;
    static const std::string BURIED_TREASURE_SOURCE;
    static const std::string BURIED_TREASURE_SOURCE_ADJECTIVE;
    static const std::string SHIPWRECK_MESSAGE;
    static const std::string SHIPWRECK_SHIP_NAME;
    static const std::string SHIPWRECK_REASON;
    static const std::string SHIPWRECK_SHIP_NAME_POSSESSIVE;
    static const std::string SHIPWRECK_SHIP_NAME_POSSESSOR;
    static const std::string SHIPWRECK_SHIP_NAME_POSSESSEE;
};

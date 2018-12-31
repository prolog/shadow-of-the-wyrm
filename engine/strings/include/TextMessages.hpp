#pragma once
#include <string>
#include "Creature.hpp"
#include "CreatureFeatures.hpp"
#include "Deity.hpp"
#include "EquipmentTypes.hpp"
#include "Item.hpp"
#include "tiles.hpp"
#include "Spell.hpp"

class TextMessages
{
  public:
    static std::string get_welcome_message(const std::string& player_name, const bool new_player);
    static std::string get_death_message(const std::string& deity_death_message_sid);
    static std::string get_player_description(const std::string& player_name);
    static std::string get_npc_escapes_message(const std::string& creature_description);
    static std::string get_action_not_found_message(const std::string& command_action);
    static std::string get_dumping_character_message(const std::string& creature_name);
    static std::string get_sex(const CreatureSex sex);
    static std::string get_sex_abrv(const CreatureSex sex);
    static std::string get_name_and_title(CreaturePtr creature);
    static std::string get_carrying_capacity_message(CreaturePtr creature);
    static std::string get_equipment_location(const EquipmentWornLocation location);
    static std::string get_confirmation_message(const std::string& query_or_sid);
    static std::string get_area_entrance_message_given_terrain_type(const TileType type);
    static std::string get_item_drop_message(const bool blind, ItemPtr item);
    static std::string get_item_pick_up_message(const bool player_blind, CreaturePtr creature, ItemPtr item);
    static std::string get_item_pick_up_and_merge_message(const bool player_blind, CreaturePtr creature, ItemPtr item);
    static std::string get_item_on_ground_description_message(const bool blind, ItemPtr item);
    static std::string get_currency_amount_message(const uint currency_amount);
    static std::string get_unpaid_amount_message(const uint unpaid_amount);
    static std::string get_reflexive_pronoun(CreaturePtr creature);
    static std::string get_experience_synopsis(const int level, const int exp, const int exp_required, const int next_level, const std::string& race_name, const float r_mult, const std::string class_name, const float c_mult);
    static std::string get_special_day_message(const std::string& day_name_sid, const std::string& day_desc_sid);
    static std::string get_engraving_message(const std::string& engraving_sid);
    static std::string get_inscription_message(const std::string& inscription_sid);
    static std::string get_replacement_message(const std::string& message, const std::string& replace);
    static std::string get_bool_sid(const bool val);
    static std::string get_character_creation_synopsis(const CreatureSex cs, RacePtr race, ClassPtr cur_class, DeityPtr cur_deity);
    static std::string get_slot_machine_message(const int cost, const int pct_chance_win, const int payout_amount);
    static std::string get_slot_machine_outcome_message(const std::string& first_sid, const std::string& second_sid, const std::string& third_sid);

  protected:
    TextMessages();
    ~TextMessages();

    static const std::string WELCOME_MESSAGE;
    static const std::string WELCOME_BACK_MESSAGE;
    static const std::string DUMPING_CHARACTER_MESSAGE;
    static const std::string ITEM_DROP_MESSAGE;
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
    static const std::string SLOT_MACHINE_MESSAGE;
    static const std::string SLOT_MACHINE_OUTCOME_MESSAGE;
    static const std::string CARRYING_CAPACITY_MESSAGE;
};

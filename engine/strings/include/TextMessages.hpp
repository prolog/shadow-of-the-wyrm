#pragma once
#include <string>
#include "CreatureFeatures.hpp"
#include "EquipmentTypes.hpp"
#include "Item.hpp"
#include "tiles.hpp"
#include "Spell.hpp"

class TextMessages
{
  public:
    static std::string get_welcome_message(const std::string& player_name, const bool new_player);
    static std::string get_death_message(const std::string& deity_death_message_sid);
    static std::string get_npc_escapes_message(const std::string& creature_description);
    static std::string get_action_not_found_message(const std::string& command_action);
    static std::string get_dumping_character_message(const std::string& creature_name);
    static std::string get_sex(const CreatureSex sex);
    static std::string get_equipment_location(const EquipmentWornLocation location);
    static std::string get_confirmation_message(const std::string& query_sid);
    static std::string get_area_entrance_message_given_terrain_type(const TileType type);
    static std::string get_item_drop_message(const std::string& item_description, const uint quantity_dropped);
    static std::string get_item_pick_up_message(ItemPtr item);
    static std::string get_item_pick_up_and_merge_message(ItemPtr item);
    static std::string get_item_on_ground_description_message(ItemPtr item);
    static std::string get_currency_amount_message(const uint currency_amount);

  protected:
    TextMessages();
    ~TextMessages();

    static const std::string WELCOME_MESSAGE;
    static const std::string WELCOME_BACK_MESSAGE;
    static const std::string DUMPING_CHARACTER_MESSAGE;
    static const std::string ITEM_DROP_MESSAGE;
    static const std::string ITEM_PICK_UP_MESSAGE;
    static const std::string ITEM_PICK_UP_AND_MERGE_MESSAGE;
    static const std::string ITEM_ON_GROUND_DESCRIPTION_MESSAGE;
    static const std::string CURRENCY_MESSAGE_SINGLE;
    static const std::string CURRENCY_MESSAGE_MULTIPLE;
};

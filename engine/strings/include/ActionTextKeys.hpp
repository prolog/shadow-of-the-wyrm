#pragma once
#include <string>
#include "Spell.hpp"

class ActionTextKeys
{
  public:
    static std::string get_evoke_message(const std::string& desc_sid, const std::string& wand_desc, const bool is_player);
    static std::string get_quaff_message(const std::string& desc_sid, const std::string& potion_desc, const bool is_player);
    static std::string get_read_message(const std::string& player_read_sid, const std::string& monster_read_sid, const std::string& desc_sid, const std::string& readable_desc, const bool is_player);
    static std::string get_eat_message(const std::string& desc_sid, const std::string& consumable_desc, const bool is_player);
    static std::string get_eat_confirmation_message(const std::string& consumable_desc);
    static std::string get_full_message(const std::string& desc_sid, const std::string& consumable_desc, const bool is_player);
    static std::string get_spellcasting_message(const Spell& spell, const std::string& creature_desc_s, const bool is_player);
    static std::string get_spellcasting_cancelled_message(const std::string& creature_desc_sid, const bool is_player);
    static std::string get_bestiary_search_message(const std::string& prev_search_text);
    static std::string get_pour_message(const std::string& desc_sid, const std::string& item_desc_sid, const bool is_player);
    static std::string get_stumble_message(const std::string& desc_sid, const bool is_player);
    static std::string get_alcohol_poisoning_death_message(const std::string& desc_sid, const bool is_player);

    static const std::string ACTION_NOT_FOUND;
    static const std::string ACTION_SEARCH;
    static const std::string ACTION_SEARCH_BLIND;
    static const std::string ACTION_PICK_UP_NOT_ALLOWED;
    static const std::string ACTION_DROP_NOT_ALLOWED;
    static const std::string ACTION_DROP_NO_ITEM_SELECTED;
    static const std::string ACTION_DROP_QUANTITY_PROMPT;
    static const std::string ACTION_DROP_INVALID_QUANTITY;
    static const std::string ACTION_PICK_UP_NOTHING_ON_GROUND;
    static const std::string ACTION_MOVEMENT_BLOCKED;
    static const std::string ACTION_PLAYER_DROWNING;
    static const std::string ACTION_PLAYER_FALLING;
    static const std::string ACTION_PLAYER_OBLITERATED;
    static const std::string ACTION_PLAYER_FALL_FROM_MOUNTAIN;
    static const std::string ACTION_PLAYER_STARVING_TO_DEATH;
    static const std::string ACTION_DETECTED_HOSTILE_CREATURES;
    static const std::string ACTION_LOOK;
    static const std::string ACTION_LOOK_UNEXPLORED_TILE;
    static const std::string ACTION_LOOK_TILE_OUT_OF_RANGE;
    static const std::string ACTION_FIRE;
    static const std::string ACTION_NOTHING_HAPPENS;
    static const std::string ACTION_CHAT_NOBODY_NEARBY;
    static const std::string ACTION_CHAT_NO_RESPONSE;
    static const std::string ACTION_GET_DIRECTION;
    static const std::string ACTION_GET_CARDINAL_DIRECTION;
    static const std::string ACTION_OPEN_DOOR;
    static const std::string ACTION_CLOSE_DOOR;
    static const std::string ACTION_DOOR_DESTROYED;
    static const std::string ACTION_APPLY_NO_FEATURES_PRESENT;
    static const std::string ACTION_HANDLE_LOCK;
    static const std::string ACTION_HANDLE_LOCK_NO_KEY;
    static const std::string ACTION_BESTIARY_DISPLAY_COMMAND_FOR_TILE_SELECTION;
    static const std::string ACTION_BESTIARY_NO_SUCH_CREATURE_EXISTS;
    static const std::string ACTION_POTION_EXPLODES;
    static const std::string ACTION_AUTOMOVE_WORLD_MAP;
    static const std::string ACTION_AUTOMOVE_TOO_HUNGRY;
    static const std::string ACTION_AUTOMOVE_HOSTILE_CREATURES;
    static const std::string ACTION_KICK_WORLD_MAP;

  protected:
    ActionTextKeys();
    ~ActionTextKeys();

    static std::string get_general_message(const std::string& desc_sid, const std::string& player_message_sid, const std::string& monster_message_sid, const bool is_player);
    static std::string get_general_action_message(const std::string& desc_sid, const std::string& item_desc /* not a sid! */, const std::string& player_message_sid, const std::string& monster_message_sid, const bool is_player);
    
    static const std::string ACTION_EVOKE_PLAYER;
    static const std::string ACTION_EVOKE_MONSTER;
    static const std::string ACTION_QUAFF_PLAYER;
    static const std::string ACTION_QUAFF_MONSTER;
    static const std::string ACTION_EAT_PLAYER;
    static const std::string ACTION_EAT_MONSTER;
    static const std::string ACTION_EAT_CONFIRMATION;
    static const std::string ACTION_FULL_PLAYER;
    static const std::string ACTION_FULL_MONSTER;
    static const std::string ACTION_SPELLCASTING_CANCELLED_PLAYER;
    static const std::string ACTION_SPELLCASTING_CANCELLED_MONSTER;
    static const std::string ACTION_BESTIARY_WHICH_CREATURE;
    static const std::string ACTION_BESTIARY_PREVIOUS_SEARCH_MESSAGE;
    static const std::string ACTION_POUR_PLAYER;
    static const std::string ACTION_POUR_MONSTER;
    static const std::string ACTION_STUMBLE_PLAYER;
    static const std::string ACTION_STUMBLE_MONSTER;
    static const std::string ACTION_ALCOHOL_POISONING_PLAYER;
    static const std::string ACTION_ALCOHOL_POISONING_MONSTER;
    static const std::string ACTION_ENCHANT_ITEM_MAX;
};

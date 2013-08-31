#pragma once
#include <string>

class EffectTextKeys
{
  public:
    static std::string get_healing_effect_message(const std::string& monster_desc_sid, const bool is_player);
    static std::string get_ether_effect_message(const std::string& monster_desc_sid, const bool is_player);
    static std::string get_identify_individual_item_message(const std::string& unid_usage_desc_sid, const std::string& id_usage_desc_sid);
    static std::string get_teleport_effect_message(const std::string& monster_desc_sid, const bool is_player);
    static std::string get_wand_recharge_message(const std::string& wand_desc_sid);
    static std::string get_wand_recharge_already_full_message(const std::string& wand_desc_sid);

    static const std::string EFFECT_NULL;
    static const std::string EFFECT_SWEET_TASTE;
    static const std::string EFFECT_FRUIT_JUICE;
    static const std::string EFFECT_IDENTIFY_ALL_ITEMS;
    static const std::string EFFECT_IDENTIFY_TYPE;
    static const std::string EFFECT_RECHARGING_PLAYER_NO_WANDS;
    
  protected:
    EffectTextKeys();
    ~EffectTextKeys();
    
    static std::string get_general_effect_message(const std::string& monster_desc_sid, const bool is_player, const std::string& player_message_sid, const std::string& monster_message_sid);

    static const std::string EFFECT_HEALING_PLAYER;
    static const std::string EFFECT_HEALING_MONSTER;
    static const std::string EFFECT_ETHER_PLAYER;
    static const std::string EFFECT_ETHER_MONSTER;
    static const std::string EFFECT_IDENTIFY_ITEM;
    static const std::string EFFECT_TELEPORT_PLAYER;
    static const std::string EFFECT_TELEPORT_MONSTER;
    static const std::string EFFECT_RECHARGING;
    static const std::string EFFECT_RECHARGING_ALREADY_FULL;
};


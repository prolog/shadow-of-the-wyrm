#pragma once
#include "DecisionStrategy.hpp"
#include "Spell.hpp"

// An abstract class that represents the base class for decision strategies
// for monsters and other NPCs.
class NPCDecisionStrategy : public DecisionStrategy
{
  public:
    NPCDecisionStrategy(ControllerPtr new_controller);
    virtual ~NPCDecisionStrategy() = default;

    virtual bool get_move_to_dangerous_tile(MapPtr map, CreaturePtr creature, TilePtr tile) const override;

    virtual CommandPtr get_decision(const bool reprompt_on_cmd_not_found, const std::string& this_creature_id, CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands, MapPtr view_map = nullptr, int* key_p = 0) override;
    virtual CommandPtr get_nonmap_decision(const bool reprompt_on_cmd_not_found, const std::string& this_creature_id, CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands, int* key_p, const bool refresh_window = true) override;

    virtual void set_fov_map(MapPtr map) override;

    virtual uint get_count(const uint max_count) override;
    virtual bool get_confirmation(const bool confirmation_default_value = false, const bool require_proper_selection = false) override;
    virtual bool get_attack_confirmation(CreaturePtr creature);

    std::string get_orders_description_sid() const override;

  protected:
    // Functions that are called based on the factory type
    virtual CommandPtr get_decision_for_map(const std::string& this_creature_id, CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands, MapPtr view_map);

    bool has_movement_orders() const;
    virtual CommandPtr get_magic_decision(const std::string& this_creature_id, MapPtr view_map);
    virtual CommandPtr get_breed_decision(const std::string& this_creature_id, MapPtr view_map);
    virtual CommandPtr get_kick_decision(const std::string& this_creature_id, MapPtr view_map);
    virtual CommandPtr get_attack_decision(const std::string& this_creature_id, MapPtr view_map);
    virtual CommandPtr get_ranged_attack_decision(const std::string& this_creature_id, MapPtr view_map);
    virtual CommandPtr get_custom_decision(const std::string& this_creature_id, MapPtr view_map);
    virtual CommandPtr get_pick_up_decision(const std::string& this_creature_id, MapPtr view_map);
    virtual CommandPtr get_drop_decision(const std::string& this_creature_id, MapPtr view_map);
    virtual CommandPtr get_use_item_decision(const std::string& this_creature_id, MapPtr view_map);
    virtual CommandPtr get_movement_decision(const std::string& this_creature_id, MapPtr view_map);
    virtual CommandPtr get_flee_decision(const std::string& this_creature_id, MapPtr view_map);
    virtual std::vector<Coordinate> get_adjacent_safe_coordinates_without_creatures(MapPtr current_map, const std::vector<Coordinate>& all_adjacent_coordinates, std::shared_ptr<Creature> creature);

    virtual CommandPtr get_decision_for_inventory(CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands) = 0;
    virtual CommandPtr get_decision_for_equipment(CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands) = 0; 
    virtual CommandPtr get_decision_for_tile_selection(CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands) = 0;
    virtual CommandPtr get_follow_direction(MapPtr view_map, CreaturePtr creature, const Coordinate& this_creature_coord, const std::string& follow_id);

    virtual void turn_to_fight(CreaturePtr creature);
    virtual void update_threats_based_on_fov(const std::string& this_creature_id, MapPtr view_map);
    virtual void update_threats_with_contraband(const std::string& this_creature_id, MapPtr view_map);
    virtual void update_threats_to_leader(const std::string& this_creature_id, MapPtr view_map);
    virtual void remove_threats_with_same_deity(const std::string& this_creature_id, MapPtr view_map);
    virtual void update_threats_if_shopkeeper(MapPtr current_fov_map);
    virtual std::vector<std::pair<std::string, int>> get_creatures_by_distance(CreaturePtr creature, MapPtr view_map, const std::set<std::string>& creature_ids);

    virtual bool should_flee(CreaturePtr this_creature, MapPtr view_map);
    virtual Coordinate select_safest_random_coordinate(CreaturePtr creature, const std::vector<Coordinate>& c);

    static const int PERCENT_CHANCE_USE_ITEM;
    static const int PERCENT_CHANCE_PICK_UP_USEFUL_ITEM;
    static const int PERCENT_CHANCE_DROP_ITEM;
    static const int PERCENT_CHANCE_ADVANCE_TOWARDS_TARGET;
    static const int PERCENT_CHANCE_CONSIDER_USING_MAGIC;
    static const int PERCENT_CHANCE_CONSIDER_RANGED_COMBAT;
    static const int PERCENT_CHANCE_BREED;
    static const int PERCENT_CHANCE_KICK_OFF_LEDGE;
    static const int PERCENT_CHANCE_KICK_REGULAR_COMBAT;
};

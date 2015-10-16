#pragma once
#include "DecisionStrategy.hpp"

// An abstract class that represents the base class for decision strategies
// for monsters and other NPCs.
class NPCDecisionStrategy : public DecisionStrategy
{
  public:
    NPCDecisionStrategy(ControllerPtr new_controller);

    virtual CommandPtr get_decision(const bool reprompt_on_cmd_not_found, const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, MapPtr view_map = nullptr, int* key_p = 0) override;
    virtual CommandPtr get_nonmap_decision(const bool reprompt_on_cmd_not_found, const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, int* key_p) override;

    virtual uint get_count(const uint max_count) override;
    virtual bool get_confirmation(const bool confirmation_default_value = false) override;
    
  protected:
    // Functions that are called based on the factory type
    virtual CommandPtr get_decision_for_map(const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, MapPtr view_map);

    virtual CommandPtr get_attack_decision(const std::string& this_creature_id, MapPtr view_map);

    virtual CommandPtr get_movement_decision(const std::string& this_creature_id);
    virtual std::vector<Coordinate> get_adjacent_safe_coordinates_without_creatures(MapPtr current_map, const std::vector<Coordinate>& all_adjacent_coordinates, std::shared_ptr<Creature> creature);

    virtual CommandPtr get_decision_for_inventory(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands) = 0;
    virtual CommandPtr get_decision_for_equipment(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands) = 0; 
    virtual CommandPtr get_decision_for_tile_selection(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands) = 0;

    static const int PERCENT_CHANCE_ADVANCE_TOWARDS_TARGET;
};

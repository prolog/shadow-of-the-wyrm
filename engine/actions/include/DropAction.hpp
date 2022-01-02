#pragma once
#include "IActionManager.hpp"
#include "Game.hpp"

class ActionManager;

class DropAction : public IActionManager
{
  public:
    ActionCostValue drop(CreaturePtr creature, ActionManager * const am);
    ActionCostValue drop(CreaturePtr creature, const std::string& drop_item_id);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
  
  protected:
    void handle_world_drop(CreaturePtr creature);
    void handle_item_dropped_message(CreaturePtr creature, IInventoryPtr inv, ItemPtr item);
    void handle_seed_planted_message(CreaturePtr creature, ItemPtr seed);
    void handle_no_item_dropped(CreaturePtr creature);
    void handle_invalid_drop_quantity(CreaturePtr creature);
    void handle_reacting_creature_drop_scripts(CreaturePtr creature, MapPtr current_map, ItemPtr new_item, const Coordinate& drop_coord);
    bool plant_seed(CreaturePtr creature, const std::string& tree_species_id, const Coordinate& coords, TilePtr tile, MapPtr current_map);
    bool bury_remains(CreaturePtr creature, const std::string& remains_race_id, const uint quantity, const Coordinate& coords, TilePtr tile, MapPtr current_map);
    bool build_with_dropped_item(CreaturePtr creature, MapPtr map, TilePtr tile, const bool building_material, const std::string& wall_tile_type_s, const std::string& floor_tile_type_s, const std::string& feature_ids);
    bool build_wall_with_dropped_item(CreaturePtr creature, MapPtr map, TilePtr tile, const TileType wall_tile_type);
    bool build_floor_with_dropped_item(CreaturePtr creature, MapPtr map, TilePtr tile, const TileType floor_tile_type);
    bool build_feature_with_dropped_item(CreaturePtr creature, MapPtr map, TilePtr tile, const std::vector<std::string>& feature_s_class_ids);
    
    ActionCostValue do_drop(CreaturePtr creature, MapPtr current_map, ItemPtr item, const bool multi_item);
    uint get_drop_quantity(CreaturePtr creature, const uint max_quantity) const;
};

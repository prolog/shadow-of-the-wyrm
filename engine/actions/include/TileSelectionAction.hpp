#pragma once
#include "IActionManager.hpp"
#include "SelectTileTypes.hpp"

enum struct TileReset
{
  TILE_RESET_ON_CREATURE,
  TILE_RESET_ON_PREV_TARGET
};

class TileSelectionAction : public IActionManager, ISerializable
{
  public:
    bool operator==(const TileSelectionAction& tsa) const;

    void set_selection_key(const std::string& new_selection_key);
    
    void set_keyboard_command_map(const KeyboardCommandMapPtr new_command_map);
    KeyboardCommandMapPtr get_keyboard_command_map();
    
    // Functions used to set whether to display certain properties.
    //
    // Everything should be shown if the creature is looking around,
    // but only creatures should be shown if the creature is doing
    // ranged combat, for example.
    void set_show_tile_description(const bool tile_desc);
    bool get_show_tile_description() const;
    
    void set_show_feature_description(const bool feature_desc);
    bool get_show_feature_description() const;
    
    void set_show_creature_description(const bool creature_desc);
    bool get_show_creature_description() const;
    
    void set_show_item_descriptions(const bool item_descs);
    bool get_show_item_descriptions() const;
    
    ActionCostValue select_tile(CreaturePtr creature, const std::string& initial_message_sid, const TileReset tre);
    ActionCostValue select_tile(CreaturePtr creature, const Direction d);
    ActionCostValue select_tile(CreaturePtr creature, const SelectCreatureType sct);
    ActionCostValue select_tile_cancel(CreaturePtr creature);
    TilePtr get_cursor_tile();
    
    bool is_tile_in_range_and_add_message_if_not(CreaturePtr creature, AttackType attack_type) const;
    
    bool remove_target(CreaturePtr creature, const AttackType attack_type);

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    friend class RangedCombatAction;
    friend class SW_Engine_Actions_TileSelectionAction; // test fixture
    TileSelectionAction();

    void reset_cursor_appropriately(CreaturePtr creature, MapPtr current_map, const TileReset tre);
    void describe_current_tile(CreaturePtr creature, TilePtr selected_tile, const bool does_tile_exist_in_fov_map);

    // The command factory/map
    CommandFactoryPtr command_factory;
    KeyboardCommandMapPtr kb_command_map;
    
    // The text to display initially
    std::string selection_key;

    // Used to control whether certain parts of the overall description are suppressed.
    bool show_tile_description;
    bool show_feature_description;
    bool show_creature_description;
    bool show_item_descriptions;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

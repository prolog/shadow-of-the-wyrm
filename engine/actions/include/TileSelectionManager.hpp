#pragma once
#include "IActionManager.hpp"

class TileSelectionManager : public IActionManager, ISerializable
{
  public:
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
    
    ActionCostValue select_tile(CreaturePtr creature, const std::string& initial_message_sid);
    ActionCostValue select_tile(CreaturePtr creature, const Direction d);
    ActionCostValue select_tile_cancel(CreaturePtr creature);
    
    bool is_tile_in_range_and_add_message_if_not(CreaturePtr creature, AttackType attack_type) const;
    
    bool remove_target(CreaturePtr creature, const AttackType attack_type);

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  protected:
    friend class ActionManager;
    friend class RangedCombatActionManager;
    TileSelectionManager();

    ActionCostValue get_action_cost_value() const;
    
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
    ClassIdentifier internal_class_identifier() const;
};

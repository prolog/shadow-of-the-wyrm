#pragma once
#include "IActionManager.hpp"
#include "Creature.hpp"
#include "SpellShapeProcessor.hpp"
#include "SpellSelectionScreen.hpp"

class SpellcastingAction : public IActionManager
{
  public:
    // Player-specific version of cast_spell
    ActionCostValue cast_spell(CreaturePtr creature) const;

    // The following version of cast_spell is meant for NPCs
    ActionCostValue cast_spell(CreaturePtr creature, const std::string& spell_id, const Direction direction = Direction::DIRECTION_NULL) const;

    // Show the arcana for a particular spell.
    ActionCostValue describe_spell(CreaturePtr creature, const std::string& spell_id);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    void add_no_magical_knowledge_message(CreaturePtr creature) const;
    void add_invalid_spellcasting_location_message(CreaturePtr creature) const;
    void add_insufficient_power_message(CreaturePtr creature) const;
    void add_spell_bonus_increased_message(CreaturePtr creature) const;
    void add_no_deities_message(CreaturePtr creature) const;
    void train_skills(CreaturePtr creature, const Spell& spell) const;

    std::pair<std::string, ActionCostValue> cast_spell_on_valid_map_type(CreaturePtr creature) const;
    std::pair<bool, std::pair<std::string, ActionCostValue>> process_spellcasting_selection(CreaturePtr creature) const;

    // Helper functions for the main cast_spell function
    //
    // Reduce the caster's AP appropriately.
    void reduce_caster_ap_by_spell_cost(CreaturePtr caster, const Spell& spell) const;

    // Handle reducing/removing castings after a successful cast.
    void reduce_castings_or_remove_spell(CreaturePtr caster, const Spell& spell) const;

    // When a spell requires a direction (beams, etc), get the direction from
    // the creature.
    std::pair<bool, Direction> get_spell_direction_from_creature(CreaturePtr caster, const Spell& spell, const Direction spell_direction) const;

    // Update the spell's bonus information.
    void update_spell_bonus(CreaturePtr caster, const Spell& spell) const;

    static const int PCT_CHANCE_MARK_MAGIC;
    static const int PCT_CHANCE_MARK_CATEGORY;
};

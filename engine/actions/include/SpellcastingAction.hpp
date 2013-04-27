#pragma once
#include "IActionManager.hpp"
#include "Creature.hpp"
#include "SpellShapeProcessor.hpp"

class SpellcastingAction : public IActionManager
{
  public:
    ActionCostValue cast_spell(CreaturePtr creature) const;
    
  protected:
    friend class ActionManager;
    SpellcastingAction();

    // Internal spellcasting function that is called by the basic cast_spell(creature)
    // function.
    ActionCostValue cast_spell(CreaturePtr creature, const std::string& spell_id) const;

    void add_no_magical_knowledge_message() const;
    void add_invalid_spellcasting_location_message() const;
    void add_insufficient_power_message() const;

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
    std::pair<bool, Direction> get_spell_direction_from_creature(CreaturePtr caster, const Direction spell_direction) const;
    // Get and process the spell's animation, followed by the spell damage and
    // effect.
    void process_animation_and_spell(SpellShapeProcessorPtr spell_processor, CreaturePtr caster, MapPtr map, const Coordinate& caster_coord, const Direction spell_direction, const Spell& spell) const;
    
    ActionCostValue get_action_cost_value() const;
};

#pragma once
#include "IActionManager.hpp"
#include "Wand.hpp"

class ItemIdentifier;
class ActionManager;

class EvokeAction : public IActionManager
{
  public:
    ActionCostValue evoke(CreaturePtr creature, ActionManager * const am);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    ActionCostValue evoke_wand(CreaturePtr creature, ActionManager * const am, WandPtr wand);
    void add_evocation_message(CreaturePtr creature, WandPtr wand, const ItemIdentifier& item_id);
    Spell create_wand_spell(CreaturePtr creature, WandPtr wand, const Direction dir) const;
    void reduce_wand_charges_if_necessary(CreaturePtr creature, WandPtr wand) const;
    bool process_wand_damage_and_effect(CreaturePtr creature, MapPtr map, const Coordinate& caster_coord, const Direction spell_direction, const Spell& wand_spell, const ItemStatus wand_status, const Statistic& original_charges);
    void name_wand_if_identified(CreaturePtr creature, WandPtr wand, const bool wand_identified, const bool wand_originally_identified, const ItemIdentifier& item_id) const;
    bool check_on_world_map(CreaturePtr creature);

    std::pair<bool, Direction> get_evocation_direction(CreaturePtr creature, const SpellShapeType shape_type);
};

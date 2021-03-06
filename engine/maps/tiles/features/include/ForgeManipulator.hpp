#pragma once
#include "ActionManager.hpp"
#include "FeatureManipulator.hpp"
#include "Feature.hpp"

class ForgeManipulator : public FeatureManipulator
{
  public:
    ForgeManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
    bool drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item) override;

  protected:
    virtual bool check_creature_passes_prerequisites(CreaturePtr creature);
    bool check_creature_knows_smithing(CreaturePtr creature);
    bool check_creature_wielding_hammer(CreaturePtr creature);
    virtual bool check_creature_has_ingots(CreaturePtr creature);

    virtual ItemPtr get_selected_ingot(CreaturePtr creature, ActionManager& am);
    virtual ItemPtr get_selected_item(CreaturePtr creature, ItemPtr ingot, ActionManager& am);

    void improve_item(CreaturePtr creature, ItemPtr selected_item, ItemPtr selected_ingot);

    virtual SkillType get_primary_crafting_skill() const;
};


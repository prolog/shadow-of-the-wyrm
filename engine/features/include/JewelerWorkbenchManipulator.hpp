#pragma once
#include "ForgeManipulator.hpp"
#include "Feature.hpp"

// A Jeweler's Workbench is basically a forge for precious metals, where
// they can be worked into existing pieces of jewelry to make something
// masterful.
class JewelerWorkbenchManipulator : public ForgeManipulator
{
  public:
    JewelerWorkbenchManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;

  protected:
    virtual bool check_creature_passes_prerequisites(CreaturePtr creature) override;
    bool check_creature_has_jewelry_skill(CreaturePtr creature);
    virtual bool check_creature_has_ingots(CreaturePtr creature) override;

    virtual ItemPtr get_selected_ingot(CreaturePtr creature, ActionManager& am) override;
    virtual ItemPtr get_selected_item(CreaturePtr creature, ItemPtr ingot, ActionManager& am) override;
};


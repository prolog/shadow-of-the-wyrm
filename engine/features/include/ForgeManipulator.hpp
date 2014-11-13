#pragma once
#include "ActionManager.hpp"
#include "IFeatureManipulator.hpp"
#include "Feature.hpp"

class ForgeManipulator : public IFeatureManipulator
{
  public:
    ForgeManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;

  protected:
    bool check_creature_passes_prerequisites(CreaturePtr creature);
    bool check_creature_knows_smithing(CreaturePtr creature);
    bool check_creature_wielding_hammer(CreaturePtr creature);
    bool check_creature_has_ingots(CreaturePtr creature);

    ItemPtr get_selected_ingot(CreaturePtr creature, ActionManager& am);
    ItemPtr get_selected_item(CreaturePtr creature, ItemPtr ingot, ActionManager& am);

    void improve_item(CreaturePtr creature, ItemPtr selected_item, ItemPtr selected_ingot);
};


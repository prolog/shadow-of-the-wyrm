#pragma once
#include "IFeatureManipulator.hpp"
#include "Feature.hpp"

class TanneryManipulator : public IFeatureManipulator
{
  public:
    TanneryManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;

  protected:
    void add_no_skins_message(CreaturePtr creature);
    void add_successful_armour_creation_message(CreaturePtr creature);

    ItemPtr create_hide_armour(CreaturePtr creature, ItemPtr selected_skin, const EquipmentWornLocation slot);

    std::map<EquipmentWornLocation, std::string> skin_items;
};


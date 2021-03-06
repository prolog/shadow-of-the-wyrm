#pragma once
#include "FeatureManipulator.hpp"
#include "Feature.hpp"

class TanneryManipulator : public FeatureManipulator
{
  public:
    TanneryManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
    bool drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item) override;

  protected:
    void add_no_skins_message(CreaturePtr creature);
    void add_successful_armour_creation_message(CreaturePtr creature);

    ItemPtr create_hide_equipment(CreaturePtr creature, ItemPtr selected_skin, const EquipmentWornLocation slot);

    std::map<EquipmentWornLocation, std::string> skin_items;
};


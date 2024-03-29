#pragma once
#include <memory>
#include "WorldMapTile.hpp"

class VillageTile : public WorldMapLandmarkTile
{
  public:
    // Villages are situated "on" something, and that subtype
    // is the underlying map upon which the village is placed.
    // If no subtype is provided, Field is assumed.
    VillageTile();
    VillageTile(const TileType new_tile_subtype);
    bool operator==(const VillageTile& vt) const;

    virtual bool display_description_on_arrival() const override;
    
    TileType get_tile_type() const override;
    
    std::string get_tile_description_sid() const override;
    
    void set_village_race_id(const std::string& new_race_id);
    std::string get_village_race_id() const;

    void set_village_name(const std::string& new_name);
    std::string get_village_name() const;
    
    void set_settlement_type(const SettlementType settlement_type);
    SettlementType get_settlement_type() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

    virtual Tile* clone() override;

  protected:
    std::string village_race_id;
    SettlementType settlement_type;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using VillageTilePtr = std::shared_ptr<VillageTile>;

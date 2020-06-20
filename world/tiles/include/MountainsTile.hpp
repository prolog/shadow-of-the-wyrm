#pragma once
#include "WorldMapTile.hpp"

class MountainsTile : public WorldMapTile
{
  public:
    TileType get_tile_type() const override;
    std::string get_tile_description_sid() const override;
    bool get_dangerous(CreaturePtr creature) const override;
    std::string get_danger_confirmation_sid() const override;
    virtual bool get_is_blocking(std::shared_ptr<Creature> perspective_creature = nullptr) const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};


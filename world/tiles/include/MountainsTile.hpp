#pragma once
#include "WorldMapTile.hpp"

class MountainsTile : public WorldMapTile
{
  public:
    TileType get_tile_type() const override;
    std::string get_tile_description_sid() const override;
    bool get_danger_flag(CreaturePtr creature) const override;
    std::string get_danger_confirmation_sid() const override;
    virtual bool get_is_blocking_visually(std::shared_ptr<Creature> perspective_creature = nullptr) const override;
    SkillType get_treasure_skill() const;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};


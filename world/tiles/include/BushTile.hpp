#pragma once
#include "Tile.hpp"

class BushTile : public Tile
{
  public:
    BushTile();

    TileType get_tile_type() const override;
    
    std::string get_tile_description_sid() const override;
    virtual std::string get_dig_message_sid() const override;

    virtual TileType get_decomposition_tile_type() const override;
    virtual std::vector<std::pair<std::pair<int, int>, std::string>> get_decomposition_item_ids() const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};


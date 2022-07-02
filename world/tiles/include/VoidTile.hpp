#pragma once
#include "Tile.hpp"

class VoidTile : public Tile
{
  public:
    TileType get_tile_type() const override;
    
    std::string get_tile_description_sid() const override;
    virtual std::string get_no_exit_up_message_sid() const;
    virtual std::string get_no_exit_down_message_sid() const;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};


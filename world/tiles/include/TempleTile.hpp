#pragma once
#include "WorshipSiteTile.hpp"

class TempleTile : public WorshipSiteTile
{
  public:
    TempleTile();
    TempleTile(const TileType subtype);

    TileType get_tile_type() const override;

    std::string get_tile_description_sid() const override;

    virtual Tile* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

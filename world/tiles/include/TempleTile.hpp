#pragma once
#include "WorshipSiteTile.hpp"

class TempleTile : public WorshipSiteTile
{
  public:
    TempleTile();
    TempleTile(const TileType subtype);

    TileType get_tile_type() const;

    std::string get_tile_description_sid() const;

    virtual Tile* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

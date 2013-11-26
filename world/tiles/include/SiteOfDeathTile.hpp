#pragma once
#include "WorshipSiteTile.hpp"

class SiteOfDeathTile : public WorshipSiteTile
{
  public:  
    SiteOfDeathTile();
    SiteOfDeathTile(const TileType subtype);

    TileType get_tile_type() const override;

    std::string get_tile_description_sid() const override;

    virtual Tile* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

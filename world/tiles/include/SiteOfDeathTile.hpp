#pragma once
#include "WorshipSiteTile.hpp"

class SiteOfDeathTile : public WorshipSiteTile
{
  public:
    SiteOfDeathTile();
    SiteOfDeathTile(const TileType subtype);
  
    TileType get_tile_type() const;

    std::string get_tile_description_sid() const;
};

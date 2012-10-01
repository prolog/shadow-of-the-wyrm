#pragma once
#include <boost/serialization/base_object.hpp>
#include "WorldMapTile.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class CastleTile : public WorldMapLandmarkTile
{
  public:
    TileType get_tile_type() const;

    std::string get_tile_description_sid() const;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<WorldMapLandmarkTile>(*this);
    }
};

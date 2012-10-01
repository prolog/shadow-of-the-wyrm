#pragma once
#include <boost/serialization/base_object.hpp>
#include "Tile.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

// Individual floor tile, raised up.
// Will have a slightly different colour to distinguish it.
class DaisTile : public Tile
{
  public:
    TileType get_tile_type() const;
    
    std::string get_tile_description_sid() const;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Tile>(*this);
    }
};

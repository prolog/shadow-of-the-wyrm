#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/serialization/base_object.hpp>
#include "StaircaseTile.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class DownStaircaseTile : public StaircaseTile
{
  public:
    TileType get_tile_type() const;
    StaircaseType get_staircase_type() const;
    
    std::string get_tile_description_sid() const;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<StaircaseTile>(*this);
    }
};

typedef boost::shared_ptr<DownStaircaseTile> DownStaircaseTilePtr;

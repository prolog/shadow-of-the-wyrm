#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/serialization/base_object.hpp>
#include "WorldMapTile.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class VillageTile : public WorldMapLandmarkTile
{
  public:
    // Villages are situated "on" something, and that subtype
    // is the underlying map upon which the village is placed.
    // If no subtype is provided, Field is assumed.
    VillageTile();
    VillageTile(const TileType new_tile_subtype);
    
    virtual bool display_description_on_arrival() const;
    
    TileType get_tile_type() const;
    
    std::string get_tile_description_sid() const;
    
    void set_village_race_id(const std::string& new_race_id);
    std::string get_village_race_id() const;
    
    void set_settlement_type(const SettlementType settlement_type);
    SettlementType get_settlement_type() const;
    
  protected:
    std::string village_race_id;
    SettlementType settlement_type;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<WorldMapLandmarkTile>(*this);
      ar & village_race_id & settlement_type;
    }
};

typedef boost::shared_ptr<VillageTile> VillageTilePtr;

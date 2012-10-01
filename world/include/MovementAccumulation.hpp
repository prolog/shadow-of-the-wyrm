#pragma once
#include "common.hpp"
#include "MovementTypes.hpp"
#include "tiles.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

// Measures the accumulation of movement across tile types and super types, given a particular method.
// This is essentially an endurance tracker.  A character with a low swim score can swim, but not for
// a particularly long time.  As a result, the system needs to track how long they've been on a
// water-type tile when not using a boat.
//
// Another example is mountaineering: a character with a reasonable mountaineering score can cross
// mountains, but attempting to scale an entire range without resting (by loading one of the mountain
// maps) will likely lead to certain doom.
class MovementAccumulation
{
  public:
    MovementAccumulation();

    void reset();
    
    void set_minutes_on_super_type_given_movement(const ulonglong new_minutes);
    ulonglong get_minutes_on_super_type_given_movement() const;

    void set_tile_super_type(const TileSuperType new_super_type);
    TileSuperType get_tile_super_type() const;

    void set_minutes_on_tile_type_given_movement(const ulonglong new_minutes);
    ulonglong get_minutes_on_tile_type_given_movement() const;

    void set_tile_type(const TileType tile_type);
    TileType get_tile_type() const;

    void set_movement_type(const MovementType new_method);
    MovementType get_movement_type() const;

  protected:
    // Later add a map to track movement across various
    // tile types, etc., for challenge purposes?
    ulonglong minutes_on_super_type_given_movement;
    TileSuperType tile_super_type;
    ulonglong minutes_on_tile_type_given_movement;
    TileType tile_type;
    MovementType movement_type;

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & minutes_on_super_type_given_movement;
      ar & tile_super_type;
      ar & minutes_on_tile_type_given_movement;
      ar & tile_type & movement_type;
    }
};

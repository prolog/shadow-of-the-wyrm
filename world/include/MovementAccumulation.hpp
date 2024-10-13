#pragma once
#include "common.hpp"
#include "MovementTypes.hpp"
#include "tiles.hpp"
#include "ISerializable.hpp"

// Measures the accumulation of movement across tile types and super types, given a particular method.
// This is essentially an endurance tracker.  A character with a low swim score can swim, but not for
// a particularly long time.  As a result, the system needs to track how long they've been on a
// water-type tile when not using a boat.
//
// Another example is mountain lore: a character with a reasonable mountain lore score can cross
// mountains, but attempting to scale an entire range without resting (by loading one of the mountain
// maps) will likely lead to certain doom.
class MovementAccumulation : public ISerializable
{
  public:
    MovementAccumulation();
    virtual bool operator==(const MovementAccumulation& movement) const;

    // Reset all the MovementAccumulation variables
    void reset();

    // Reset only the time-related variables (used when things like water
    // breathing wear off so the PC doesn't immediately start drowning.
    void reset_minutes();
    
    void set_minutes_on_super_type_given_movement(const ulonglong new_minutes);
    ulonglong get_minutes_on_super_type_given_movement() const;

    void set_tile_super_type(const TileSuperType new_super_type);
    TileSuperType get_tile_super_type() const;

    void set_minutes_on_tile_type_given_movement(const ulonglong new_minutes);
    ulonglong get_minutes_on_tile_type_given_movement() const;

    void set_tile_type(const TileType tile_type);
    TileType get_tile_type() const;

    void set_tile_frozen(const bool frozen);
    bool get_tile_frozen() const;

    void set_movement_type(const MovementType new_method);
    MovementType get_movement_type() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    // Later add a map to track movement across various
    // tile types, etc., for challenge purposes?
    ulonglong minutes_on_super_type_given_movement;
    TileSuperType tile_super_type;
    ulonglong minutes_on_tile_type_given_movement;
    TileType tile_type;
    bool frozen;
    MovementType movement_type;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

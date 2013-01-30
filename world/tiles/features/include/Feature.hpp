#pragma once
#include <boost/shared_ptr.hpp>
#include "common.hpp"
#include "Lock.hpp"
#include "Trap.hpp"
#include "Material.hpp"
#include "ISerializable.hpp"

// An abstract base class representing a dungeon feature.  A feature is
// like an item, but cannot move.  Examples include fireplaces, thrones,
// bookshelves, levers, etc.
//
// Features can be trapped.
class Feature : public ISerializable
{
  public:
    Feature(const MaterialType new_material);
    Feature(const Feature& feature);
    Feature& operator=(const Feature& feature);

    virtual ~Feature() {};
    virtual Feature* clone() = 0;
    virtual bool operator==(const Feature& feature);

    // If a feature is blocking, the square it occupies cannot be
    // occupied by another creature, and any items thrown, kicked, etc.,
    // in its direction will stop before reaching the tile.
    virtual bool get_is_blocking() const;

    // Display information.
    virtual uchar get_symbol()  const = 0;
    virtual Colour get_colour() const; // by default, use the material's colour.
    
    virtual bool has_trap() const;
    virtual void set_trap(TrapPtr new_trap);
    virtual TrapPtr get_trap();

    virtual void set_lock(LockPtr new_lock);
    virtual LockPtr get_lock();

    virtual void set_material_type(const MaterialType new_material);
    virtual MaterialType get_material_type() const;
    
    virtual std::string get_description_sid() const = 0;
    
    virtual bool can_kick() const;
    virtual bool can_offer() const;
    virtual bool can_open() const;
    virtual bool can_lock() const;

    virtual bool kick() = 0;
    virtual bool offer();
    virtual bool open();

    // Can the feature be handled, given whether the tile it is on is
    // currently occupied?
    virtual bool can_handle(const bool feature_tile_occupied) const;
    virtual bool handle() = 0;
    // Potential handle message for the current feature.
    // By default, returns the empty SID.
    virtual std::string get_handle_message_sid() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    TrapPtr trap;
    LockPtr lock;
    MaterialType material;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Feature> FeaturePtr;

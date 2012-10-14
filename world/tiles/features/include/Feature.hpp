#pragma once
#include <boost/shared_ptr.hpp>
#include "common.hpp"
#include "Lock.hpp"
#include "Trap.hpp"
#include "Material.hpp"

// An abstract base class representing a dungeon feature.  A feature is
// like an item, but cannot move.  Examples include fireplaces, thrones,
// bookshelves, levers, etc.
//
// Features can be trapped.
class Feature
{
  public:
    Feature(MaterialPtr new_material);
    virtual ~Feature() {};

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

    virtual void set_material(MaterialPtr new_material);
    virtual MaterialPtr get_material();
    
    virtual std::string get_description_sid() const = 0;
    
    virtual bool can_handle() const;
    virtual bool can_kick() const;
    virtual bool can_offer() const;
    virtual bool can_open() const;
    virtual bool can_lock() const;

    virtual bool kick() = 0;
    virtual bool handle() = 0;
    virtual bool offer();
    virtual bool open();

  protected:
    TrapPtr trap;
    LockPtr lock;
    MaterialPtr material;
};

typedef boost::shared_ptr<Feature> FeaturePtr;

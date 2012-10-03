#pragma once
#include <boost/shared_ptr.hpp>
#include "common.hpp"
#include "IHandleable.hpp"
#include "IKickable.hpp"
#include "ITrappable.hpp"
#include "Material.hpp"

// An abstract base class representing a dungeon feature.  A feature is
// like an item, but cannot move.  Examples include fireplaces, thrones,
// bookshelves, levers, etc.
//
// Features can be trapped.
class Feature : public ITrappable, public IHandleable, public IKickable
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
    
    virtual void set_trap(TrapPtr new_trap);
    virtual TrapPtr get_trap();

    virtual void set_material(MaterialPtr new_material);
    virtual MaterialPtr get_material();
    
    virtual std::string get_description_sid() const = 0;

  protected:
    TrapPtr trap;
    MaterialPtr material;
};

typedef boost::shared_ptr<Feature> FeaturePtr;

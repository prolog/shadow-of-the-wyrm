#pragma once
#include <map>
#include <boost/shared_ptr.hpp>
#include "tiles.hpp"
#include "Inventory.hpp"
#include "Creature.hpp"
#include "Directions.hpp"
#include "Feature.hpp"
#include "Item.hpp"
#include "ISerializable.hpp"
#include "MapExit.hpp"

typedef std::map<Direction, MapExitPtr> TileExitMap;

class Creature;

class Tile : public ISerializable
{
  public:
    // No public constructor - making tiles copyable would be bad, because then all the various shared pointers
    // associated with them would also be copied, which might not be intended.  Use TileGenerator to ensure each
    // copy starts fresh.
    virtual ~Tile();
    
    virtual std::string get_tile_description_sid() const = 0;
    
    // By default, this is false, but certain tiles (such as overland tiles, staircases, etc.)
    // will be shown on each move.
    virtual bool display_description_on_arrival() const;

    virtual void set_illuminated(bool new_illuminated);
    virtual bool get_illuminated() const;
    
    virtual bool get_is_blocking() const;
    virtual int get_movement_multiplier() const;

    // This is player-centric.  Probably OK for now, but may need to be
    // revisited later.
    virtual void set_explored(bool new_explored);
    virtual bool get_explored() const;
    
    virtual void set_viewed(bool new_viewed);
    virtual bool get_viewed() const;

    // Features include doors, windows, thrones, fireplaces...
    virtual bool has_feature() const;
    virtual bool has_blocking_feature() const;
    virtual void set_feature(FeaturePtr new_feature);
    virtual FeaturePtr get_feature();

    virtual bool has_creature() const;
    virtual void set_creature(const boost::shared_ptr<Creature>& new_creature);
    virtual void remove_creature();
    virtual boost::shared_ptr<Creature> get_creature() const;
    
    virtual Inventory& get_items();

    virtual TileType get_tile_type() const;
    virtual TileSuperType get_tile_super_type() const;

    virtual void     set_tile_subtype(const TileType new_tile_subtype);
    virtual TileType get_tile_subtype() const;
    
    virtual TileExitMap& get_tile_exit_map_ref();
    
    virtual bool get_dangerous() const;
    virtual std::string get_danger_confirmation_sid() const;
    
    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

    virtual Tile* clone() = 0;

  protected:
    Tile();

    virtual void set_default_properties();

    bool illuminated;
    bool explored;
    bool viewed;

    // This is defined by each class, and shouldn't be overridden
    // by means of a set function.
    TileType tile_type;
    TileType tile_subtype;

    // Each tile can have at most one creature on it.
    boost::shared_ptr<Creature> creature;
    
    // Each tile can have at most one feature on it.
    FeaturePtr feature;

    // Each tile can have any number of items piled up on it.
    // Re-use the basic inventory data type for this purpose.
    Inventory items;
    
    // A tile can have exits in various directions. These lead to other maps/levels/etc.
    TileExitMap map_exits;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Tile> TilePtr;

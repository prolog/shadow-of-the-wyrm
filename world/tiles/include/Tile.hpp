#pragma once
#include <map>
#include <boost/shared_ptr.hpp>
#include "tiles.hpp"
#include "Creature.hpp"
#include "Directions.hpp"
#include "Item.hpp"
#include "MapExit.hpp"

typedef std::map<Direction, MapExitPtr> TileExitMap;

class Inventory;

class Tile
{
  public:
    Tile();
    ~Tile();
    
    virtual std::string get_tile_description_sid() const = 0;
    
    // By default, this is false, but certain tiles (such as overland tiles, staircases, etc.)
    // will be shown on each move.
    virtual bool display_description_on_arrival() const;

    virtual void set_illuminated(bool new_illuminated);
    virtual bool get_illuminated() const;

    // This is player-centric.  Probably OK for now, but may need to be
    // revisited later.
    virtual void set_explored(bool new_explored);
    virtual bool get_explored() const;

    virtual bool has_creature() const;
    virtual void set_creature(const CreaturePtr& new_creature);
    virtual void remove_creature();
    virtual CreaturePtr get_creature() const;
    
    virtual Inventory& get_items();

    virtual TileType get_tile_type() const;
    
    virtual TileExitMap& get_tile_exit_map_ref();
    
  protected:
    virtual void set_default_properties();

    bool illuminated;
    bool explored;

    // This is defined by each class, and shouldn't be overridden
    // by means of a set function.
    TileType tile_type;

    // Each tile can have at most one creature on it.
    CreaturePtr creature;

    // Each tile can have any number of items piled up on it.
    // Re-use the basic inventory data type for this purpose.
    Inventory items;
    
    // A tile can have exits in various directions. These lead to other maps/levels/etc.
    TileExitMap map_exits;
};

typedef boost::shared_ptr<Tile> TilePtr;

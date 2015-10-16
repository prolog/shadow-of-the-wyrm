#pragma once
#include <map>
#include <memory>
#include "Feature.hpp"
#include "tiles.hpp"
#include "IInventory.hpp"
#include "Creature.hpp"
#include "DigChances.hpp"
#include "Directions.hpp"
#include "Item.hpp"
#include "ISerializable.hpp"
#include "MapExit.hpp"
#include "TileProperties.hpp"
#include "TileTextKeys.hpp"

using TileExitMap = std::map<Direction, MapExitPtr>;

class Creature;
class Feature;

class Tile : public ISerializable
{
  public:
    // No public constructor - making tiles copyable would be bad, because then all the various shared pointers
    // associated with them would also be copied, which might not be intended.  Use TileGenerator to ensure each
    // copy starts fresh.
    virtual ~Tile();
    virtual bool operator==(const Tile& tile) const;
    
    virtual std::string get_tile_description_sid() const = 0;

    // The "extra" description is a description that is always shown when
    // moving over a tile, in addition to any other description that is
    // shown.  Can be used for signposts, warnings, etc.
    virtual void set_extra_description_sid(const std::string& new_extra_description_sid);
    virtual std::string get_extra_description_sid() const;
    virtual bool has_extra_description() const;

    // The custom map ID is a unique ID used to identify the pre-generated map
    // for a particular tile.  In most cases, this will not be needed, and the 
    // default generator (based on tile type, etc) should be used instead.  
    // But for cases where something unique is needed, this is the mechanism
    // to use.
    virtual void set_custom_map_id(const std::string& custom_map_id);
    virtual std::string get_custom_map_id() const;
    virtual bool has_custom_map_id() const;

    // The generic way to set additional properties.
    virtual void set_additional_property(const std::string& property_name, const std::string& property_value);
    virtual std::string get_additional_property(const std::string& property_name) const;
    virtual size_t remove_additional_property(const std::string& property_name);
    virtual std::map<std::string, std::string> get_additional_properties() const;
    virtual bool has_additional_property(const std::string& property_name) const;
    
    // By default, this is false, but certain tiles (such as overland tiles, staircases, etc.)
    // will be shown on each move.
    virtual bool display_description_on_arrival() const;

    virtual void set_illuminated(bool new_illuminated);
    virtual bool get_illuminated() const;
    
    virtual bool get_is_blocking(std::shared_ptr<Creature> perspective_creature = nullptr) const;
    virtual bool get_is_blocking_ignore_present_creature(std::shared_ptr<Creature> perspective_creature) const;
    virtual bool get_is_blocking_for_item(std::shared_ptr<Item> item = nullptr) const;
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
    virtual void set_feature(std::shared_ptr<Feature> new_feature);
    virtual void remove_feature();
    virtual std::shared_ptr<Feature> get_feature();

    virtual bool has_creature() const;
    virtual void set_creature(const std::shared_ptr<Creature>& new_creature);
    virtual void remove_creature();
    virtual std::shared_ptr<Creature> get_creature() const;
    
    virtual IInventoryPtr get_items();

    virtual TileType get_tile_type() const;
    virtual TileSuperType get_tile_super_type() const;
    virtual TileType get_decomposition_tile_type() const; // When digging, what does the tile break down into?
    virtual std::string get_decomposition_item_id() const;

    virtual void     set_tile_subtype(const TileType new_tile_subtype);
    virtual TileType get_tile_subtype() const;

    // Used for digging, to see if the wielded item has enough strength
    // to penetrate the tile.
    void set_hardness(const int new_hardness);
    int get_hardness() const;
    
    virtual TileExitMap& get_tile_exit_map_ref();
    
    virtual bool get_dangerous(std::shared_ptr<Creature> creature) const;
    virtual std::string get_danger_confirmation_sid() const;

    virtual float get_piety_loss_multiplier() const;

    virtual void transformFrom(std::shared_ptr<Tile> original_tile);
    
    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

    // Regeneration multipliers are used to determine how quickly it takes
    // to regeneration 1 HP/AP.  The base multiplier is 1.  A multiplier
    // less than 1 indicates quick regeneration, and greater than 1 indicates
    // slower.
    virtual float get_hp_regeneration_multiplier() const;
    virtual float get_ap_regeneration_multiplier() const;

    virtual void set_dig_chances(const DigChances& new_dig_chances);
    virtual DigChances get_dig_chances() const;

    virtual Tile* clone() = 0;

  protected:
    Tile(const int new_hardness = 0);
    Tile(const DigChances& dc);

    // Setup code common to the two constructors
    void init();

    virtual void set_default_properties();

    bool illuminated;
    bool explored;
    bool viewed;

    std::map<std::string, std::string> additional_properties;

    // This is defined by each class, and shouldn't be overridden
    // by means of a set function.
    TileType tile_type;
    TileType tile_subtype;

    // How hard is the tile? > 1 means that the tile is solid and requires
    // digging.
    int hardness;

    // Each tile can have at most one creature on it.
    std::shared_ptr<Creature> creature;
    
    // Each tile can have at most one feature on it.
    std::shared_ptr<Feature> feature;

    // Each tile can have any number of items piled up on it.
    // Re-use the basic inventory data type for this purpose.
    IInventoryPtr items;
    
    // A tile can have exits in various directions. These lead to other maps/levels/etc.
    TileExitMap map_exits;

    // When digging on this tile, what're the probabilities of certain
    // things happening?
    DigChances dig_chances;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using TilePtr = std::shared_ptr<Tile>;

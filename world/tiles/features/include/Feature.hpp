#pragma once
#include <vector>
#include <memory>
#include "AlignmentEnums.hpp"
#include "Creature.hpp"
#include "common.hpp"
#include "Lock.hpp"
#include "Material.hpp"
#include "ISerializable.hpp"

class Tile;
class Creature;

// An abstract base class representing a dungeon feature.  A feature is
// like an item, but cannot move.  Examples include fireplaces, thrones,
// bookshelves, levers, etc.
class Feature : public ISerializable
{
  public:
    Feature(const MaterialType new_material, const AlignmentRange new_alignment_range, const int uses = -1);
    Feature(const Feature& feature);
    Feature& operator=(const Feature& feature);

    virtual ~Feature() {};
    virtual Feature* clone() = 0;
    virtual bool operator==(const Feature& feature) const;

    // If a feature is blocking, the square it occupies cannot be
    // occupied by another creature, and any items thrown, kicked, etc.,
    // in its direction will stop before reaching the tile.
    virtual bool get_is_blocking() const;

    // If a feature is hidden, it won't be displayed over the tile
    // when rendering the map.
    virtual bool get_is_hidden() const;

    // Is the feature dangerous in some sense?  E.g., traps are,
    // pews aren't.
    virtual bool get_is_dangerous() const;

    // Does the feature apply on movement?  The creature moving
    // into the tile is passed so that skills/eq can be checked, etc.
    virtual bool apply_on_movement(std::shared_ptr<Creature> creature) const;

    // Display information.
    virtual uchar get_symbol()  const = 0;
    virtual Colour get_colour() const; // by default, use the material's colour.
    
    virtual void set_lock(LockPtr new_lock);
    virtual LockPtr get_lock();

    virtual void set_material_type(const MaterialType new_material);
    virtual MaterialType get_material_type() const;

    virtual std::pair<std::string, std::vector<std::string>> get_description_and_replacement_sids() const;
    
    virtual bool can_offer() const;
    virtual bool can_open() const;
    virtual bool can_lock() const;

    virtual bool offer();
    virtual bool open();

    // Can the feature be handled, given whether the tile it is on is
    // currently occupied?
    virtual bool can_handle(const bool feature_tile_occupied) const;

    // Potential handle message for the current feature.
    // By default, returns the empty SID.
    virtual std::string get_handle_message_sid() const;

    virtual float get_piety_loss_multiplier() const;

    void set_alignment_range(const AlignmentRange new_alignment_range);
    virtual AlignmentRange get_alignment_range() const;

    void set_uses(const int new_uses);
    int get_uses() const;

    virtual float get_hp_regeneration_multiplier() const;
    virtual float get_ap_regeneration_multiplier() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    virtual std::string get_description_sid() const = 0;

    LockPtr lock;
    MaterialType material;
    AlignmentRange alignment_range;
    int uses;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using FeaturePtr = std::shared_ptr<Feature>;

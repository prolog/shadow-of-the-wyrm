#pragma once
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include "EquipmentTypes.hpp"
#include "Effect.hpp"
#include "ISerializable.hpp"
#include "ItemTypes.hpp"
#include "Material.hpp"
#include "Weight.hpp"

class Effect;

class Item : public ISerializable
{
  public:
    Item();
    virtual ~Item();
    
    // A unique ID for each item
    virtual void set_id(const std::string& new_id);
    virtual std::string get_id() const;
    
    // The ID of the item in the configuration XML - used for lookup to set global values.
    virtual void set_base_id(const std::string& new_base_id);
    virtual std::string get_base_id() const;
    
    virtual void set_quantity(const uint new_quantity);
    virtual uint get_quantity() const;
    virtual bool is_valid_quantity(const uint selected_quantity) const;
    
    // Used when picking up, dropping, or otherwise describing an item.
    // E.g. (in angle brackets), "You throw <a dagger>"
    //                           "You drop <an egg>"
    //                           "You eat <a carrot>"
    virtual void set_usage_description_sid(const std::string& new_usage_description_sid);
    virtual std::string get_usage_description_sid() const;
    
    // Used to describe an item in the inventory or equipment screens.
    // E.g., "Wielded: short sword"
    virtual void set_description_sid(const std::string& new_description_sid);
    virtual std::string get_description_sid() const;
    
    virtual void set_unidentified_usage_description_sid(const std::string& new_unident_usage_description_sid);
    virtual std::string get_unidentified_usage_description_sid() const;
    
    virtual void set_unidentified_description_sid(const std::string& new_unident_description_sid);
    virtual std::string get_unidentified_description_sid() const;
    
    // Whether the item can be used as part of a read command - scrolls and spellbooks will, and all
    // other items should not set this.
    virtual void set_readable(const bool new_readable);
    virtual bool get_readable() const;
    
    virtual void set_weight(const Weight& new_weight);
    virtual Weight get_weight() const;
    
    virtual void set_worn_location(const EquipmentWornLocation new_worn_location);
    virtual EquipmentWornLocation get_worn_location() const;
    
    virtual void set_status(const ItemStatus new_status);
    virtual ItemStatus get_status() const;
    
    virtual void set_status_identified(const bool new_status_identified);
    virtual bool get_status_identified() const;
    
    virtual void set_artifact(const bool new_artifact);
    virtual bool get_artifact() const;
    
    virtual void set_type(const ItemType type);
    virtual ItemType get_type() const;
    
    virtual void set_material(MaterialPtr new_material);
    virtual MaterialPtr get_material() const;
    
    virtual void   set_symbol(const uchar new_symbol);
    virtual uchar  get_symbol() const;
    
    virtual void   set_colour(const Colour new_colour);
    virtual Colour get_colour() const;
    
    virtual void   set_identification_type(const ItemIdentificationType new_id_type);
    ItemIdentificationType get_identification_type() const;
    
    // Functions for stack management
    virtual bool matches(boost::shared_ptr<Item> item);
    
    // additional_item_attributes_match needs to be implemented by the subclasses of item.
    // It is included in the checks in matches, and is used to determine item type-specific
    // match behaviour. (e.g., potions need to match on spells, weapons need to match on
    // to-hit and damage, etc.).  The base class version just returns true.
    virtual bool additional_item_attributes_match(boost::shared_ptr<Item> i);

    virtual void set_effect(EffectPtr new_effect);
    virtual EffectPtr get_effect();
    
    virtual Item* clone() = 0;
    virtual Item* deep_copy();
    virtual Item* deep_copy_with_new_id();

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);
    
  protected:
    friend class ItemIdentifier;
    
    // Functions to check identification.  This should not be called on an individual item created from the templates -
    // rather, an instance of ItemIdentifier should be created, and this should be queried.  This class will check the
    // item templates.  This ensures that if a type of item (potion of speed, for example) is identified, any already-
    // created items on the current level will be correctly identified as well.
    virtual void set_item_identified(const bool new_item_identified);
    virtual bool get_item_identified() const;
    
    std::string id;
    std::string base_id;
    uint quantity; // the number of items in the stack
    std::string usage_description_sid; // the description is usually of the form "a foo", "an eggplant" "the fabled sword x".
    std::string description_sid; // the short description is displayed on the inventory and equipment screens.
    std::string unidentified_usage_description_sid; // the usage description seen when unidentified
    std::string unidentified_description_sid; // the description seen when the item is unidentified
    Weight weight;
    bool readable;
    EquipmentWornLocation worn_location;
    ItemStatus status;
    bool status_identified;
    bool item_identified;
    bool artifact;
    ItemType type;
    uchar symbol;
    Colour colour;
    ItemIdentificationType identification_type;

    // This needs to be deep copied.
    EffectPtr effect;
    
    // This needs to be deep copied.
    MaterialPtr material;

  private:
    virtual ClassIdentifier internal_class_identifier() const = 0;
};

typedef boost::shared_ptr<Item> ItemPtr;
typedef std::map<std::string, ItemPtr> ItemMap;

#pragma once
#include <map>
#include <string>
#include <memory>
#include "common.hpp"
#include "Colours.hpp"
#include "EquipmentTypes.hpp"
#include "EffectTypes.hpp"
#include "ISerializable.hpp"
#include "ItemTypes.hpp"
#include "MaterialTypes.hpp"
#include "Modifier.hpp"
#include "Resistances.hpp"
#include "ScriptDetails.hpp"
#include "Statistic.hpp"
#include "Symbol.hpp"
#include "Weight.hpp"

class Effect;

class Item : public ISerializable
{
  public:
    Item();
    virtual ~Item();
    bool operator==(const Item& item) const;
    
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

    virtual void set_codex_description_sid(const std::string& new_codex_description_sid);
    virtual std::string get_codex_description_sid() const;

    // The synopsis is displayed after the item's description in the inventory
    // and equipment screens, if the item is identified.  It is expected that
    // certain types of items may override this function: wands will display
    // charges, etc.
    virtual std::string get_synopsis() const;

    // Whether the item can be used as part of a read command - scrolls and spellbooks will, and all
    // other items should not set this.
    virtual void set_readable(const bool new_readable);
    virtual bool get_readable() const;
    
    virtual void set_value(const uint new_value);
    virtual uint get_value() const;
    virtual uint get_total_value() const;

    virtual void set_weight(const Weight& new_weight);
    virtual Weight get_weight() const;
    virtual Weight get_weight(const uint quantity) const;
    virtual Weight get_total_weight() const;
    
    virtual void set_worn_location(const EquipmentWornLocation new_worn_location);
    virtual EquipmentWornLocation get_worn_location() const;
    
    virtual void set_status(const ItemStatus new_status);
    virtual ItemStatus get_status() const;
    
    virtual void set_status_identified(const bool new_status_identified);
    virtual bool get_status_identified() const;
    
    // Does the item curse itself when equipped?
    virtual void set_auto_curse(const bool new_auto_curse);
    virtual bool get_auto_curse() const;

    virtual void set_artifact(const bool new_artifact);
    virtual bool get_artifact() const;

    virtual void set_hands_required(const int new_hands_required);
    int get_hands_required() const;

    virtual void set_type(const ItemType type);
    virtual ItemType get_type() const;
    virtual bool get_type_always_stacks() const;
    
    virtual void set_material_type(const MaterialType new_material);
    virtual MaterialType get_material_type() const;
    
    virtual void   set_symbol(const Symbol& new_symbol);
    virtual Symbol get_symbol() const;
    
    virtual void   set_colour(const Colour new_colour);
    virtual Colour get_colour() const;
    
    virtual void   set_identification_type(const ItemIdentificationType new_id_type);
    ItemIdentificationType get_identification_type() const;
    
    void set_lock_id(const std::string& new_lock_id);
    std::string get_lock_id() const;

    // Functions for stack management
    virtual bool matches(std::shared_ptr<Item> item) const;
    
    // additional_item_attributes_match needs to be implemented by the subclasses of item.
    // It is included in the checks in matches, and is used to determine item type-specific
    // match behaviour. (e.g., potions need to match on spells, weapons need to match on
    // to-hit and damage, etc.).  The base class version just returns true.
    virtual bool additional_item_attributes_match(std::shared_ptr<Item> i) const = 0;

    virtual void set_effect_type(const EffectType new_effect_type);
    virtual EffectType get_effect_type() const;
    
    virtual void set_glowing(const bool new_glowing);
    virtual bool get_glowing() const;

    void set_resistances(const Resistances& new_res);
    Resistances get_resistances() const;
    Resistances& get_resistances_ref();

    void set_modifier(const Modifier& new_modifier);
    Modifier get_modifier() const;

    // Whether or not the item can be enchanted/smithed.
    // If the item is an artifact, it cannot be enchanted/smithed.
    // Otherwise, this function checks to see whether the maximum number
    // of enchantments/smithings has been reached.
    virtual bool can_enchant() const;
    virtual bool can_smith() const;

    // Enchant/smith the item if possible; if this is successful, reduce the
    // number of allowable enchantments/smithings by one.
    virtual bool enchant(const int pct_chance_brand, const float enchant_mult);

    // Brand the item, typically if it's a weapon or armour.  Reduce the number
    // of allowable enchantments/smithings by one.
    virtual bool brand();
    
    // Get the resource string IDs for any flags associated with the item.
    // Generally, only weapons and armour will have flags.
    virtual std::vector<std::string> get_flag_sids() const;

    // Assume an enchant_mult of 1.0 and allow a single point of enchantment.
    // This function is used when generating better items based on the
    // danger level of the current location.
    bool enchant(const int pct_chance_brand, const int enchant_points);
    virtual bool smith(const int smith_points);

    void set_remaining_enchants(const Statistic& new_remaining);
    Statistic get_remaining_enchants() const;

    void set_remaining_smithings(const Statistic& new_remaining);
    Statistic get_remaining_smithings() const;

    void set_additional_properties(const std::map<std::string, std::string>& additional_properties);
    void set_additional_property(const std::string& property_name, const std::string& property_value);
    std::string get_additional_property(const std::string& property_name) const;
    bool has_additional_property(const std::string& property_name) const;

    std::map<std::string, std::string> get_additional_properties() const;

    void clear_event_scripts();
    void set_event_scripts(const std::map<std::string, ScriptDetails>& esm);
    std::map<std::string, ScriptDetails> get_event_scripts() const;
    void add_event_script(const std::string& event_name, const ScriptDetails& sd);
    bool has_event_script(const std::string& event_name);
    ScriptDetails get_event_script(const std::string& event_name) const;

    void set_unpaid(const bool new_unpaid);
    bool get_unpaid() const;

    // Used for NPC AI decisions
    virtual bool get_is_good() const;
    virtual int get_score() const;

    virtual void set_floats(const bool new_floats);
    bool get_floats() const;

    virtual Item* create_with_new_id();
    virtual Item* clone_with_new_id();

    // These functions create copies of the item without changing the ID.
    // This may be what you want. But it can lead to weirdness as you
    // interact with items on the ground and your inventory (because the
    // IDs are the same!).
    virtual Item* create();
    virtual Item* clone() = 0;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;
    
  protected:
    friend class ItemIdentifier;
    
    // Functions to check identification.  This should not be called on an individual item created from the templates -
    // rather, an instance of ItemIdentifier should be created, and this should be queried.  This class will check the
    // item templates.  This ensures that if a type of item (potion of speed, for example) is identified, any already-
    // created items on the current level will be correctly identified as well.
    virtual void set_item_identified(const bool new_item_identified);
    virtual bool get_item_identified() const;

    // Not all item properties are durable.  To allow for fewer stacks
    // and more intuitive stacking behaviours, some properties are
    // ignored when doing item comparison.
    std::map<std::string, std::string> get_additional_properties_for_item_comparison() const;

    // The base item class enchants/smiths by updating resistances.
    // Other items may modify nutrition (consumables), evade/soak (wearables),
    // etc.  Smithing only updates physical damage types.  Branding only
    // works for wearables and weapons.
    virtual void do_enchant_item(const int points);
    virtual void do_smith_item(const int points);
    virtual DamageType do_brand();
    DamageType get_random_brand();

    void increase_value(const int num_enchant_or_smith_points = 1);

    std::string id;
    std::string base_id;
    uint quantity; // the number of items in the stack
    std::string usage_description_sid; // the description is usually of the form "a foo", "an eggplant" "the fabled sword x".
    std::string description_sid; // the short description is displayed on the inventory and equipment screens.
    std::string unidentified_usage_description_sid; // the usage description seen when unidentified
    std::string unidentified_description_sid; // the description seen when the item is unidentified
    std::string codex_description_sid; // the description displayed in the codex

    uint value;
    Weight weight;
    bool readable;
    EquipmentWornLocation worn_location;
    ItemStatus status;
    bool status_identified;
    bool item_identified;
    bool auto_curse;
    bool artifact;
    int hands_required;
    ItemType type;
    Symbol symbol;
    Colour colour;
    ItemIdentificationType identification_type;
    EffectType effect;
    MaterialType material;
    bool glowing;
    Resistances resistances;
    Modifier modifier;
    Statistic remaining_enchants;
    Statistic remaining_smithings;
    std::map<std::string, std::string> additional_properties;
    std::map<std::string, ScriptDetails> event_scripts;
    bool unpaid;

    static const int MIN_ENCHANT_VALUE_INCR;

  private:
    virtual ClassIdentifier internal_class_identifier() const = 0;
};

using ItemPtr = std::shared_ptr<Item>;
using ItemMap = std::map<std::string, ItemPtr>;

#pragma once
#include "Damage.hpp"
#include "Item.hpp"
#include "SpellTypes.hpp"

class Wand : public Item
{
  public:
    Wand();
    ~Wand();

    bool operator==(const Wand& rhs) const;

    void set_range(const uint new_range);
    uint get_range() const;

    void set_spell_shape_type(const SpellShapeType new_shape_type);
    SpellShapeType get_spell_shape_type() const;

    void set_has_damage(const bool new_has_damage);
    bool get_has_damage() const;

    void set_damage(const Damage& new_damage);
    Damage get_damage() const;

    void reset_charges();
    void set_charges(const uint new_charges);
    uint get_charges() const;

    // Wands return a null effect type when they have no charges.
    virtual EffectType get_effect_type() const;
    
    Item* clone();

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  protected:
    uint range;
    SpellShapeType shape;
    bool has_damage;
    Damage damage;
    uint charges;

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Wand> WandPtr;

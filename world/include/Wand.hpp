#pragma once
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

    void reset_charges();
    void set_charges(const uint new_charges);
    uint get_charges() const;
    
    Item* clone();

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  protected:
    uint range;
    SpellShapeType shape;
    uint charges;

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Wand> WandPtr;

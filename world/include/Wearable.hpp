#pragma once
#include "Item.hpp"

// Wearable is an abstract class that is the parent of Weapon, Armour,
// and any other type of Item that can be worn.  It defines bonuses to
// hit, for armour, resistances, etc., that are common to both types.
class Wearable : public Item
{
  public:
    Wearable();
    virtual ~Wearable();
    
    void set_to_hit(const int new_to_hit);
    int get_to_hit() const;

    void set_addl_damage(const int new_addl_damage);
    int get_addl_damage() const;

    void set_evade(const int new_evade);
    int get_evade() const;
    
    void set_soak(const int new_soak);
    int get_soak() const;

    std::string get_synopsis() const override;
    
    virtual bool additional_item_attributes_match(std::shared_ptr<Item> i) override;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;
    
  protected:
    int evade, soak, to_hit, addl_damage;
};

typedef std::shared_ptr<Wearable> WearablePtr;

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
    
    void set_evade(const int new_evade);
    int get_evade() const;
    
    void set_soak(const int new_soak);
    int get_soak() const;
    
    virtual bool additional_item_attributes_match(boost::shared_ptr<Item> i);

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);
    
  protected:
    int evade, soak;
};

typedef boost::shared_ptr<Wearable> WearablePtr;

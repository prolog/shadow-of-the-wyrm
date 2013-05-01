#pragma once
#include "Item.hpp"

class Consumable : public Item
{
  public:
    Consumable();
    Consumable(const int nutr);
    ~Consumable();
    bool operator==(const Consumable& consumable) const;
    
    virtual ItemType get_type() const = 0;
    
    void set_nutrition(const int new_nutrition);
    int get_nutrition() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    int nutrition;
};

typedef boost::shared_ptr<Consumable> ConsumablePtr;

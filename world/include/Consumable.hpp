#pragma once
#include "Item.hpp"

class Consumable : public Item
{
  public:
    Consumable();
    Consumable(const int nutr);
    ~Consumable();
    
    virtual ItemType get_type() const = 0;
    
    void set_nutrition(const int new_nutrition);
    int get_nutrition() const;
    
  protected:
    int nutrition;
};

typedef boost::shared_ptr<Consumable> ConsumablePtr;

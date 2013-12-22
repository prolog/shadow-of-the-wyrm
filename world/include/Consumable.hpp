#pragma once
#include "Item.hpp"

class Consumable : public Item
{
  public:
    Consumable();
    Consumable(const int nutr, const float std_drinks);
    bool operator==(const Consumable& consumable) const;
    
    virtual ItemType get_type() const override = 0;
    
    void set_nutrition(const int new_nutrition);
    int get_nutrition() const;

    void set_standard_drinks(const float new_standard_drinks);
    float get_standard_drinks() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    int nutrition;
    float standard_drinks;
};

typedef std::shared_ptr<Consumable> ConsumablePtr;

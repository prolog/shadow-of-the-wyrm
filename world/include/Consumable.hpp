#pragma once
#include "Item.hpp"
#include "ConsumableConstants.hpp"

class Consumable : public Item
{
  public:
    Consumable();
    Consumable(const int nutr, const float std_drinks);
    bool operator==(const Consumable& consumable) const;

    virtual bool is_corpse() const;

    virtual void set_food_type(const FoodType new_food_type);
    virtual FoodType get_food_type() const;

    virtual ItemType get_type() const override = 0;

    void set_metabolizes_alcohol(const bool new_metabolizes_alcohol);
    bool get_metabolizes_alcohol() const;
    
    void set_nutrition(const int new_nutrition);
    int get_nutrition() const;

    void set_standard_drinks(const float new_standard_drinks);
    float get_standard_drinks() const;

    void set_poisoned(const bool new_poisoned);
    bool get_poisoned() const;

    bool additional_item_attributes_match(ItemPtr item) const override;
    bool consumable_properties_match(const Consumable& cons) const;

    int get_score() const override;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    virtual void do_enchant_item(const int points) override;
    virtual void increase_value(const int num_enchant_or_smith_points = 1) override;

    int nutrition;
    float standard_drinks;
    FoodType food_type;
    bool poisoned;
};

using ConsumablePtr = std::shared_ptr<Consumable>;

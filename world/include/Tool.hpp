#pragma once
#include "Item.hpp"

class Tool : public Item
{
  public:
    Tool();
    ~Tool();

    Item* clone() override;

    bool additional_item_attributes_match(std::shared_ptr<Item> i) const override;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using ToolPtr = std::shared_ptr<Tool>;


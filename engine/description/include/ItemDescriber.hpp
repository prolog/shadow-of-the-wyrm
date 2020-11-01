#pragma once
#include "IDescriber.hpp"
#include "Item.hpp"

class ItemDescriber : public IDescriber
{
  public:
    ItemDescriber(ItemPtr new_item);

    virtual ~ItemDescriber() {};

    virtual std::string describe() const override;
    virtual std::string describe_for_tile_selection() const override;
    virtual std::string describe_usage() const;
    virtual std::string describe_tried() const;
    virtual std::string describe_resists_and_flags() const;
    virtual std::string describe_quantity_and_value() const;

  protected:
    ItemPtr item;
};

using ItemDescriberPtr = std::unique_ptr<ItemDescriber>;
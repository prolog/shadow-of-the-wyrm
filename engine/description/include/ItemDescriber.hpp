#pragma once
#include "IDescriber.hpp"
#include "Item.hpp"

class ItemDescriber : public IDescriber
{
  public:
    ItemDescriber(ItemPtr new_item);

    virtual ~ItemDescriber() {};

    virtual std::string describe() const override;
    virtual std::string describe_usage() const;

    // Describe any additional details, i.e. desc for line2 of the eq
    // screen.
    virtual std::string describe_additional() const;

  protected:
    ItemPtr item;
};

using ItemDescriberPtr = std::shared_ptr<ItemDescriber>;
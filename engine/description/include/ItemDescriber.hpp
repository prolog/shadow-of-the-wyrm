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

  protected:
    ItemPtr item;
};

typedef std::shared_ptr<ItemDescriber> ItemDescriberPtr;
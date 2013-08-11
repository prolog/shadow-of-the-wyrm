#pragma once
#include "IDescriber.hpp"
#include "Item.hpp"

class ItemDescriber : public IDescriber
{
  public:
    ItemDescriber(ItemPtr new_item);

    virtual ~ItemDescriber() {};

    virtual std::string describe() const;

  protected:
    ItemPtr item;
};

typedef boost::shared_ptr<ItemDescriber> ItemDescriberPtr;
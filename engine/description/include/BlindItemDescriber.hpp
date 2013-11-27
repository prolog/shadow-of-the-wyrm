#pragma once
#include "ItemDescriber.hpp"
#include "Item.hpp"

class BlindItemDescriber : public IDescriber
{
  public:
    BlindItemDescriber();

    virtual std::string describe() const override;
};


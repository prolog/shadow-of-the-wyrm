#pragma once
#include "ItemDescriber.hpp"
#include "Item.hpp"

class BlindItemDescriber : public ItemDescriber
{
  public:
    BlindItemDescriber();
    virtual std::string describe() const override;
    virtual std::string describe_usage() const override;
    virtual std::string describe_resists() const override;
};


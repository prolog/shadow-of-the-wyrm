#pragma once
#include "TileDamageProcessor.hpp"

class NullTileDamageProcessor : public TileDamageProcessor
{
  protected:
    virtual bool affects_item(ItemPtr item) override;
};


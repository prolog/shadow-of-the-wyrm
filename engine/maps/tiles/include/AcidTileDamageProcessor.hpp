#pragma once
#include "TileDamageProcessor.hpp"

class AcidTileDamageProcessor : public TileDamageProcessor
{
  protected:
    virtual std::string get_message_sid() const override;
    virtual int get_pct_chance() const override;
    virtual bool affects_item(ItemPtr item) override;
};


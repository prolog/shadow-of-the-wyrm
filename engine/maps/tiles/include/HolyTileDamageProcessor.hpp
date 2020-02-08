#pragma once
#include "TileDamageProcessor.hpp"

class HolyTileDamageProcessor : public TileDamageProcessor
{
  protected:
    virtual std::string get_message_sid() const override;
    virtual int get_pct_chance() const override;
    virtual bool affects_item(ItemPtr item) override;
    virtual bool destroy_item() const override;
    virtual void process_item(ItemPtr item) override;
};


#pragma once
#include "TileDamageProcessor.hpp"

class ColdTileDamageProcessor : public TileDamageProcessor
{
  protected:
    virtual std::string get_message_sid() const override;
    virtual int get_pct_chance() const override;
    virtual bool affects_material(const MaterialType mt) override;
};


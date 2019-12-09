#pragma once
#include "Entrance.hpp"
#include "Symbol.hpp"

class Gate : public Entrance
{
  public:
    Gate(const Symbol& new_symbol);
    Gate(const Symbol& new_symbol, LockPtr new_lock, const EntranceState& new_state);
    virtual Feature* clone() override;

    virtual bool get_is_blocking() const override;
    virtual Symbol get_symbol() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

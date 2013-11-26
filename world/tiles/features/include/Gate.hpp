#pragma once
#include "Entrance.hpp"

class Gate : public Entrance
{
  public:
    Gate();
    Gate(LockPtr new_lock, const EntranceState& new_state);
    virtual Feature* clone() override;

    virtual bool handle() override;
    virtual bool kick() override;
    virtual bool get_is_blocking() const override;
    virtual uchar get_symbol() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

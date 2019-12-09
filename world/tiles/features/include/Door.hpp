#pragma once
#include "Entrance.hpp"
#include "Symbol.hpp"

// Doors are Features, but like Windows, will be re-used outside the
// dungeon environment.
class Door : public Entrance
{
  public:
    Door(const Symbol& new_symbol);
    Door(const Symbol& new_symbol, LockPtr new_lock, const EntranceState& new_state);
    virtual Feature* clone() override;

    virtual ~Door() {};

    virtual bool get_is_blocking() const override;
    virtual Symbol get_symbol()  const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
 };

using DoorPtr = std::shared_ptr<Door>;
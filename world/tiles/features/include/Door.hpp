#pragma once
#include "Entrance.hpp"

// Doors are Features, but like Windows, will be re-used outside the
// dungeon environment.
class Door : public Entrance
{
  public:
    Door();
    Door(LockPtr new_lock, const EntranceState& new_state);
    virtual Feature* clone() override;

    virtual ~Door() {};

    virtual bool handle() override;
    virtual bool kick() override;
    virtual bool get_is_blocking() const override;
    virtual uchar get_symbol()  const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
 };

typedef std::shared_ptr<Door> DoorPtr;
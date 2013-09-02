#pragma once
#include "Directions.hpp"
#include "ISerializable.hpp"

// AutomaticMovement is a class used to track automatic movement for a
// creature (typically the player).
class AutomaticMovement : public ISerializable
{
  public:
    AutomaticMovement();
    bool operator==(const AutomaticMovement& auto_m) const;

    void set_direction(const Direction new_direction);
    Direction get_direction() const;

    void set_engaged(const bool new_engaged);
    bool get_engaged() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    Direction direction;
    bool engaged;

  private:
    ClassIdentifier internal_class_identifier() const;
};


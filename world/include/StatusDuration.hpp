#pragma once
#include "common.hpp"
#include "ISerializable.hpp"

// StatusDuration describes the length of time a creature has a particular
// effect or maladie.  This could be the result of being poisoned,
// silenced, etc., or it could be the result of a spell.
class StatusDuration : public ISerializable
{
  public:
    explicit StatusDuration();
    explicit StatusDuration(const double end);

    bool operator==(const StatusDuration& sd) const;

    void set_end(const double new_end_val);
    double get_end() const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);


  protected:
    double end;

  private:
    ClassIdentifier internal_class_identifier() const;
};


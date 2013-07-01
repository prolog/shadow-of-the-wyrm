#pragma once
#include "common.hpp"
#include "ISerializable.hpp"

// StatusDuration describes the length of time a creature has a particular
// effect or maladie.  This could be the result of being poisoned,
// silenced, etc., or it could be the result of a spell.
class StatusDuration : public ISerializable
{
  public:
    StatusDuration();
    StatusDuration(const ulonglong start, const ulonglong duration);
    bool operator==(const StatusDuration& sd) const;

    void set_start_time(const ulonglong new_start_time);
    ulonglong get_start_time() const;

    void set_duration_length(const ulonglong new_duration_length);
    ulonglong get_duration_length() const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);


  protected:
    ulonglong start_time;
    ulonglong duration_length;

  private:
    ClassIdentifier internal_class_identifier() const;
};


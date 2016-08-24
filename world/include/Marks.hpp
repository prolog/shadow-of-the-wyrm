#pragma once
#include "ISerializable.hpp"

// Implements the concept of "marks", for skills, statistics, etc.
class Marks : public ISerializable
{
  public:
    Marks();
    Marks(const int new_marks);

    bool operator==(const Marks& m) const;

    void set_value(const int new_marks);
    int  get_value() const;
    void incr();

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    ClassIdentifier internal_class_identifier() const override;

    int marks;
};


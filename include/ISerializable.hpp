#pragma once
#include <iostream>
#include "ClassIdentifiers.hpp"

// An interface that must be implemented by all serializable objects.
//
// serialize returns true if the object was saved correctly from the
// provided ostream, false otherwise.
//
// deserialize returns true if the object was loaded correctly from
// the provided istream, false otherwise.
//
// get_class_identifier() returns a class identifier that should
// uniquely identify the class, and is written out prior to the
// class' data.  E.g.:
//
// Class ObjectWithOtherObjects:
//
//     std::vector<SomeBaseClass*>
//
//     serialize:
//         for each SomeBaseClass* in the vector, write the Class ID,
//         then call SomeBaseClassInstance->serialize(ostream);
//
class ISerializable
{
  public:
    virtual ~ISerializable() {};

    virtual bool serialize(std::ostream& stream) = 0;
    virtual bool deserialize(std::istream& stream) = 0;

    virtual ClassIdentifier get_class_identifier() const { return internal_class_identifier(); }

  private:
    // This function is private and pure virtual so that it has to be implemented, and so that each class has a
    // unique value.  If A -> B -> C, and B implements the function, it will be private and so C cannot just use
    // B's version.
    virtual ClassIdentifier internal_class_identifier() const = 0;
};


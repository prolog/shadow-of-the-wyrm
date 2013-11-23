#pragma once
#include <memory>
#include "ISerializable.hpp"

class Trap : public ISerializable
{
  public:
    Trap();
    virtual ~Trap() {};
    bool operator==(const Trap& trap) const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef std::shared_ptr<Trap> TrapPtr;

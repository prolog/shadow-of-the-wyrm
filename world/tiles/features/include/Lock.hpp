#pragma once
#include <boost/shared_ptr.hpp>
#include "ISerializable.hpp"

class Lock : public ISerializable
{
  public:
    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Lock> LockPtr;

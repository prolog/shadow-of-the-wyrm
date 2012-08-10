#pragma once
#include <string>
#include <boost/shared_ptr.hpp>

class IDescriber
{
  public:
    virtual ~IDescriber();
    virtual std::string describe() const = 0;
};

typedef boost::shared_ptr<IDescriber> IDescriberPtr;

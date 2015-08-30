#pragma once
#include <string>
#include <memory>

class IDescriber
{
  public:
    virtual ~IDescriber();
    virtual std::string describe() const = 0;
};

using IDescriberPtr = std::shared_ptr<IDescriber>;

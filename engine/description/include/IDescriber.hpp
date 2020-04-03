#pragma once
#include <string>
#include <memory>

class IDescriber
{
  public:
    virtual ~IDescriber();
    virtual std::string describe() const = 0;
};

using IDescriberPtr = std::unique_ptr<IDescriber>;

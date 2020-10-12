#pragma once
#include <string>
#include <memory>

class IDescriber
{
  public:
    virtual ~IDescriber();
    virtual std::string describe() const = 0;
    virtual std::string describe_for_tile_selection() const;
};

using IDescriberPtr = std::unique_ptr<IDescriber>;

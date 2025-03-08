#pragma once
#include <memory>
#include <string>
#include "Item.hpp"

class CodexDescriber
{
  public:
    CodexDescriber(ItemPtr item);
    virtual ~CodexDescriber() = default;

    virtual std::string describe_for_synopsis_line() const;
    virtual std::string describe_resistances() const;
    virtual std::string describe_speed_bonus() const;
    virtual std::string describe_details() const;

  protected:
    ItemPtr item;
};

using CodexDescriberPtr = std::unique_ptr<CodexDescriber>;

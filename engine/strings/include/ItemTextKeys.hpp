#pragma once
#include <string>
#include "common.hpp"

class ItemTextKeys
{
  public:
    static const std::string ITEM_GLOW;
    static const std::string ITEM_MULTIPLE;

    static std::string get_value(const uint value);

  protected:
    ItemTextKeys();
    ~ItemTextKeys();

    static const std::string ITEM_VALUE;
};

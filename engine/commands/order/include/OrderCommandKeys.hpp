#pragma once
#include <string>

class OrderCommandKeys
{
  public:
    static const std::string ATTACK;
    static const std::string FOLLOW;
    static const std::string FREEZE;
    static const std::string EXIT_ORDER;

  protected:
    OrderCommandKeys();
    ~OrderCommandKeys();
};
#pragma once
#include <string>

class OrderCommandKeys
{
  public:
    static const std::string ATTACK;
    static const std::string FOLLOW;
    static const std::string FREEZE;
    static const std::string AT_EASE;
    static const std::string EXIT_ORDER;
    static const std::string SUMMON;

  protected:
    OrderCommandKeys();
    ~OrderCommandKeys();
};
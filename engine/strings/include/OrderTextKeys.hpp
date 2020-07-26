#pragma once
#include <string>

class OrderTextKeys
{
  public:
    static const std::string ORDER_ATTACK;
    static const std::string ORDER_FOLLOW;
    static const std::string ORDER_FREEZE;

    static const std::string GIVE_ORDER_ATTACK;
    static const std::string GIVE_ORDER_FOLLOW;
    static const std::string GIVE_ORDER_FREEZE;

  protected:
    OrderTextKeys();
    ~OrderTextKeys();
};

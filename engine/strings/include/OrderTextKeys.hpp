#pragma once
#include <string>

class OrderTextKeys
{
  public:
    // If you update any of these, remember to also update NPCDecisionStrategy.
    static const std::string ORDER_ORDERS;
    static const std::string ORDER_ATTACK;
    static const std::string ORDER_FOLLOW;
    static const std::string ORDER_FREEZE;
    static const std::string ORDER_AT_EASE;
    static const std::string ORDER_SUMMON;

    static const std::string GIVE_ORDER_ATTACK;
    static const std::string GIVE_ORDER_FOLLOW;
    static const std::string GIVE_ORDER_FREEZE;
    static const std::string GIVE_ORDER_AT_EASE;
    static const std::string GIVE_ORDER_SUMMON;

  protected:
    OrderTextKeys();
    ~OrderTextKeys();
};

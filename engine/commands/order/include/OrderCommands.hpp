#pragma once
#include "Command.hpp"

class OrderAttackCommand : public Command
{
  public:
    OrderAttackCommand(const int key);
};

class OrderFollowCommand : public Command
{
  public:
    OrderFollowCommand(const int key);
};

class OrderFreezeCommand : public Command
{
  public:
    OrderFreezeCommand(const int key);
};

class OrderExitCommand : public Command
{
  public:
    OrderExitCommand(const int key);
};

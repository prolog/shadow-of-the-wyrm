#pragma once
#include "Controller.hpp"
#include "DecisionStrategy.hpp"

class PlayerDecisionStrategy : public DecisionStrategy
{
  public:
    PlayerDecisionStrategy(ControllerPtr new_controller);

  protected:
    ControllerPtr controller;
};

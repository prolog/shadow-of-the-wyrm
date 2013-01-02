#pragma once
#include "Creature.hpp"
#include "Map.hpp"

class DeathEventFunctionNames
{
  public:
    static const std::string DEATH_EVENT_WIN;

  protected:
    DeathEventFunctionNames();
    ~DeathEventFunctionNames();
};

class DeathEventFunctions
{
  public:
    // null should be called when a lookup fails - this function will do absolutely nothing.
    static void null(boost::shared_ptr<Creature> attacking, boost::shared_ptr<Creature> dead, boost::shared_ptr<Map> map);
    static void win(boost::shared_ptr<Creature> attacking, boost::shared_ptr<Creature> dead, boost::shared_ptr<Map> map);

  protected:
    DeathEventFunctions();
    ~DeathEventFunctions();
};

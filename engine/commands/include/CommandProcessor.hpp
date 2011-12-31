#pragma once
#include "Commands.hpp"
#include "Creature.hpp"

class CommandProcessor
{
  public:
    static void process(CreaturePtr creature, CommandPtr command);

  protected:
    CommandProcessor();
    ~CommandProcessor();

    static void process_command(CreaturePtr creature, Command* command);
    static void process_directional_command(CreaturePtr creature, DirectionalCommand* command);
};

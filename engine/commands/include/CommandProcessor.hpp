#pragma once
#include "Commands.hpp"
#include "Creature.hpp"
#include "Display.hpp"

// Return values of true mean "advance to next creature".  false indicates
// failure, and that the creature should be allowed to repeat.  Things like
// checking the game version, trying to move off the world map, etc., will
// return false.  Successfully moving, attacking, etc., return true.
class CommandProcessor
{
  public:
    static bool process(CreaturePtr creature, CommandPtr command, DisplayPtr display);

  protected:
    CommandProcessor();
    ~CommandProcessor();

    static bool process_command(CreaturePtr creature, Command* command, DisplayPtr display);
    static bool process_directional_command(CreaturePtr creature, DirectionalCommand* command, DisplayPtr display);
    static bool process_confirmation(CreaturePtr creature, Command* command, DisplayPtr display);
};

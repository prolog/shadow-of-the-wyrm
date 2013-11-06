#pragma once
#include <string>
#include <vector>
#include "common.hpp"
#include "Creature.hpp"

class ScriptEngine;

// Class that encapsulates running a level script.  LevelScript will set
// the appropriate values into the scripting engine, and then call the
// standard level function.  This will ensure that the scripting
// environment has all the information it needs to handle the level up.
class LevelScript
{
  public:
    void execute(ScriptEngine& se, const std::vector<std::string>& setup_scripts, CreaturePtr creature);

  protected:
    static const std::string LEVEL_MODULE_NAME;
    static const std::string LEVEL_FUNCTION_NAME;
};


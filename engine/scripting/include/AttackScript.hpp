#pragma once
#include <string>
#include "Creature.hpp"

class ScriptEngine;

// Class that encapsulates an attack script.  Each attack calls
// a particular function (set in a lookup table by the attacking
// creature's base ID), passing it the attacked creature's ID as
// a parameter.
class AttackScript
{
  public:
    bool execute(ScriptEngine& se, const std::string& attack_script, CreaturePtr attacking_creature, const std::string& attacked_creature_id);

  protected:
    static const std::string ATTACK_MODULE_NAME;
    static const std::string ATTACK_FUNCTION_NAME;
};


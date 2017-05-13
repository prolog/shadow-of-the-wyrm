#pragma once
#include <string>
#include "Map.hpp"

class ScriptEngine;

class MapScript
{
  public:
    bool execute(ScriptEngine& se, const std::string& map_script, MapPtr map);

  protected:
    static const std::string MAP_MODULE_NAME;
    static const std::string MAP_FUNCTION_NAME;
};


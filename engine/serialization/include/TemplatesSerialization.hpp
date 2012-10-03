#pragma once
#include <ostream>
#include "SerializationTypes.hpp"

class Game;

class TemplatesSerialization
{
  public:
    static void save(std::ostream& stream, Game* game);
    static SerializationReturnCode load();
};


#pragma once
#include <ostream>
#include "SerializationTypes.hpp"

class Game;

class GameEngineSerialization
{
  public:
    static void save(std::ostream& stream, Game* game);
    static SerializationReturnCode load();
};

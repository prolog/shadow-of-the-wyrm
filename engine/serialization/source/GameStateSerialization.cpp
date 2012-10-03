#include "Game.hpp"
#include "GameStateSerialization.hpp"

void GameStateSerialization::save(std::ostream& stream, Game* game)
{
}

SerializationReturnCode GameStateSerialization::load()
{
  return SERIALIZATION_OK;
}

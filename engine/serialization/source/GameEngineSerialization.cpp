#include "Game.hpp"
#include "GameEngineSerialization.hpp"


#include "GameEngineExports.hpp"

void GameEngineSerialization::save(std::ostream& stream, Game* game)
{
}

SerializationReturnCode GameEngineSerialization::load()
{
  return SERIALIZATION_OK;
}

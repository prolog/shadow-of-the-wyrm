#include <boost/serialization/base_object.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/vector.hpp>
#include "Game.hpp"
#include "GameEngineSerialization.hpp"


#include "GameEngineExports.hpp"

void GameEngineSerialization::save(boost::archive::text_oarchive& ar, Game* game)
{
  ar << game->ac << game->time_keeper << game->game_command_factory;
  ar << game->game_kb_command_map;
}

SerializationReturnCode GameEngineSerialization::load()
{
  return SERIALIZATION_OK;
}

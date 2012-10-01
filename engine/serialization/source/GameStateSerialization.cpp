#include "Game.hpp"
#include "GameStateSerialization.hpp"

void GameStateSerialization::save(boost::archive::text_oarchive& ar, Game* game)
{
  ar << game->keep_playing << game->reload_game_loop << game->game_instance /* ignore display */;
  ar << game->current_world_ix << game->current_map_id;
}

SerializationReturnCode GameStateSerialization::load()
{
  return SERIALIZATION_OK;
}

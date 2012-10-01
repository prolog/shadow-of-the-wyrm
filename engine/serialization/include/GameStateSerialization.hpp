#pragma once
#include <boost/archive/text_oarchive.hpp>
#include "SerializationTypes.hpp"

class Game;

// Serializes the bits and bobs needed to run the game object - mostly
// flags and things like that.  The heavy lifting is done by other
// classes.
class GameStateSerialization
{
  static void save(boost::archive::text_oarchive& ar, Game* game);
  static SerializationReturnCode load();
};


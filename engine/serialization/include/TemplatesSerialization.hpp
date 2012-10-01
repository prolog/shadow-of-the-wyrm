#pragma once
#include <boost/archive/text_oarchive.hpp>
#include "SerializationTypes.hpp"

class Game;

class TemplatesSerialization
{
  public:
    static void save(boost::archive::text_oarchive& ar, Game* game);
    static SerializationReturnCode load();
};


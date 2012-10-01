#pragma once
#include "Creature.hpp"
#include "Environment.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include "SerializationTypes.hpp"

class Serialization
{
  public:
    static void save(CreaturePtr creature);
    static SerializationReturnCode load();
};


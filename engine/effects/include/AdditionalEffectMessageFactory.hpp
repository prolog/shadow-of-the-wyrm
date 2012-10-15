#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "AdditionalEffectMessage.hpp"

typedef std::map<ClassIdentifier, AdditionalEffectMessagePtr> AdditionalMessageSerializationMap;

class AdditionalEffectMessageFactory
{
  public:
    static AdditionalEffectMessagePtr create_additional_effect_message(const ClassIdentifier clid);

  protected:
    AdditionalEffectMessageFactory();
    ~AdditionalEffectMessageFactory();

    static void initialize_messages();

    static AdditionalMessageSerializationMap message_map;
};


#include <boost/make_shared.hpp>
#include "AdditionalEffectMessageFactory.hpp"
#include "AdditionalEffectMessages.hpp"

using namespace std;

AdditionalMessageSerializationMap AdditionalEffectMessageFactory::message_map;

AdditionalEffectMessageFactory::AdditionalEffectMessageFactory()
{
}

AdditionalEffectMessageFactory::~AdditionalEffectMessageFactory()
{
}

AdditionalEffectMessagePtr AdditionalEffectMessageFactory::create_additional_effect_message(const ClassIdentifier clid)
{
  AdditionalEffectMessagePtr message;

  if (message_map.empty())
  {
    initialize_messages();
  }

  AdditionalMessageSerializationMap::iterator a_it = message_map.find(clid);

  if (a_it != message_map.end())
  {
    message = AdditionalEffectMessagePtr(a_it->second->clone());
  }

  return message;
}

void AdditionalEffectMessageFactory::initialize_messages()
{
  message_map.clear();

  AdditionalEffectMessagePtr sweet = boost::make_shared<SweetTasteEffectMessage>();
  
  message_map.insert(make_pair(CLASS_ID_SWEET_TASTE_EFFECT_MESSAGE, sweet)); 
}

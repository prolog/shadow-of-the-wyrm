#include "FeatureManager.hpp"
#include "MessageManager.hpp"
#include "StringTable.hpp"

using namespace std;

FeatureManager::FeatureManager()
{
}

FeatureManager::~FeatureManager()
{
}

bool FeatureManager::handle(FeaturePtr feature)
{
  bool result = false;

  if (feature && feature->can_handle())
  {
    result = feature->handle();

    if (result)
    {
      string handle_message = StringTable::get(feature->get_handle_message_sid());

      if (!handle_message.empty())
      {
        MessageManager* manager = MessageManager::instance();

        if (manager)
        {
          manager->add_new_message(handle_message);
          manager->send();
        }
      }
    }
  }

  return result;
}


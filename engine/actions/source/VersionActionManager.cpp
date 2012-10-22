#include "global_prototypes.hpp"
#include "MessageManager.hpp"
#include "Metadata.hpp"
#include "VersionActionManager.hpp"

using std::string;

VersionActionManager::VersionActionManager()
{
}

ActionCostValue VersionActionManager::version() const
{
  Metadata meta;
  MessageManager* manager = MessageManager::instance();
  string game_version = meta.get_game_version_synopsis();

  manager->add_new_message(game_version);
  manager->send();
  
  return get_action_cost_value();
}

ActionCostValue VersionActionManager::get_action_cost_value() const
{
  return 0;
}

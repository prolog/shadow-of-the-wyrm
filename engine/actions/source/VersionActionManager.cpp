#include "global_prototypes.hpp"
#include "MessageManager.hpp"
#include "VersionActionManager.hpp"

using std::string;

void VersionActionManager::version() const
{
  MessageManager* manager = MessageManager::instance();
  string game_version = get_game_version_synopsis();

  manager->add_new_message(game_version);
  manager->send();
}
uint VersionActionManager::get_current_action_cost() const
{
  return 0;
}

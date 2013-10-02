#include "global_prototypes.hpp"
#include "MessageManagerFactory.hpp"
#include "Metadata.hpp"
#include "VersionAction.hpp"

using std::string;

VersionAction::VersionAction()
{
}

ActionCostValue VersionAction::version() const
{
  Metadata meta;
  IMessageManager& manager = MessageManagerFactory::instance();
  string game_version = meta.get_full_game_version_details();

  manager.add_new_message(game_version);
  manager.send();
  
  return get_action_cost_value();
}

ActionCostValue VersionAction::get_action_cost_value() const
{
  return 0;
}

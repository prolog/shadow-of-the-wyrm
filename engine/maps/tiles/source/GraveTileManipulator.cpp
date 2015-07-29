#include "GraveTileManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "CreatureActions.hpp"
#include "DefaultTileManipulator.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"

bool GraveTileManipulator::dig(CreaturePtr creature, TilePtr tile)
{
  bool dug = false;

  if (creature != nullptr && tile != nullptr)
  {
    // Get the default dig message.
    DefaultTileManipulator dft;
    dug = dft.dig(creature, tile);

    creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_NO_GRAVEDIGGING);
	Game::instance().get_deity_action_manager_ref().notify_action(creature, CreatureActionKeys::ACTION_GRAVEROBBING);

    // Add a message about disturbing the dead.
    if (creature->get_is_player())
    {
      IMessageManager& manager = MessageManagerFactory::instance();
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_GRAVE));

      manager.send();
    }

    // Break the appropriate conduct
    // ...

    // Graverobbing is an action many of the nine do not approve of...
  }

  return dug;
}

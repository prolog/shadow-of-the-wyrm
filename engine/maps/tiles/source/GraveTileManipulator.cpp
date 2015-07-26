#include "GraveTileManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "DefaultTileManipulator.hpp"
#include "MessageManagerFactory.hpp"

bool GraveTileManipulator::dig(CreaturePtr creature, TilePtr tile)
{
  bool dug = false;

  if (creature != nullptr && tile != nullptr)
  {
    // Get the default dig message.
    DefaultTileManipulator dft;
    dug = dft.dig(creature, tile);

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

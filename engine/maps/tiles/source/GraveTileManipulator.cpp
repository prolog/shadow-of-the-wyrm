#include "GraveTileManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "CreatureActions.hpp"
#include "DefaultTileManipulator.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"

bool GraveTileManipulator::dig(CreaturePtr creature, MapPtr map, TilePtr tile)
{
  bool dug = false;

  if (creature != nullptr && tile != nullptr)
  {
    // Get the default dig message.
    DefaultTileManipulator dft;
    dug = dft.dig(creature, map, tile);

    creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_NO_GRAVEDIGGING);

    // Graverobbing is an action many of the Nine do not approve of...
    if (!tile->has_additional_property(TileProperties::TILE_PROPERTY_PREVIOUSLY_DUG))
    {
      Game::instance().get_deity_action_manager_ref().notify_action(creature, map, CreatureActionKeys::ACTION_GRAVEROBBING);
    }

    // Add a message about disturbing the dead.
    if (creature->get_is_player())
    {
      IMessageManager& manager = MMF::instance();
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_GRAVE));

      manager.send();
    }
  }

  return dug;
}

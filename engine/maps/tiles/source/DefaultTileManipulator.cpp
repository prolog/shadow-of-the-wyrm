#include "DefaultTileManipulator.hpp"
#include "ActionTextKeys.hpp"
#include "MessageManagerFactory.hpp"

DefaultTileManipulator::DefaultTileManipulator()
  : super_type_message_sids({ { TileSuperType::TILE_SUPER_TYPE_GROUND, ActionTextKeys::ACTION_DIG_GROUND },
                             { TileSuperType::TILE_SUPER_TYPE_WATER, ActionTextKeys::ACTION_DIG_WATER },
                             { TileSuperType::TILE_SUPER_TYPE_AIR, ActionTextKeys::ACTION_DIG_AIR } })
{
}

// Add a default digging message based on the creature and the tile super
// type - "Splash!" for water, "Whoosh!" for air, etc.
bool DefaultTileManipulator::dig(CreaturePtr creature, TilePtr tile)
{
  bool dug = false;

  if (creature != nullptr && tile != nullptr)
  {
    TileSuperType super_type = tile->get_tile_super_type();

    if (creature->get_is_player())
    {
      IMessageManager& manager = MessageManagerFactory::instance();

      auto s_it = super_type_message_sids.find(super_type);
      if (s_it != super_type_message_sids.end())
      {
        manager.add_new_message(StringTable::get(super_type_message_sids[super_type]));
        manager.send();

      }
    }

    dug = true;
  }

  return dug;
}


#pragma once
#include "ITileManipulator.hpp"

// Default tile manipulator.  Defines manipulation operations that do
// very little - if there's any tile-specific behaviour, the factory
// will instantiate a different class.
class DefaultTileManipulator : public ITileManipulator
{
  public:
    DefaultTileManipulator();

    bool dig(CreaturePtr creature, TilePtr tile) override;

  protected:
    std::map<TileSuperType, std::string> super_type_message_sids;
};


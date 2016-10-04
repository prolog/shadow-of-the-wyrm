#include "ActionTextKeys.hpp"
#include "AltarManipulator.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

AltarManipulator::AltarManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

bool AltarManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_HANDLE_ALTAR));
    manager.send();
  }

  return true;
}

bool AltarManipulator::drop(CreaturePtr creature, ItemPtr item)
{
  bool item_altered = false;

  if (creature != nullptr && item != nullptr)
  {
    AlignmentRange altar_range = feature->get_alignment_range();
    AlignmentRange creature_range = creature->get_alignment().get_alignment_range();

    if (altar_range == creature_range)
    {
      // ...
    }
    else
    {
      // ...
    }
  }

  return item_altered;
}

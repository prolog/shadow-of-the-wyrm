#include "TrapManipulator.hpp"
#include "MessageManagerFactory.hpp"
#include "Trap.hpp"

using namespace std;

TrapManipulator::TrapManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void TrapManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  // JCD FIXME add a message about "narrowly setting off the trap"...
}

bool TrapManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  FeaturePtr feature = tile->get_feature();
  TrapPtr trap = dynamic_pointer_cast<Trap>(feature);

  if (trap)
  {
    string trigger_message_sid = trap->get_trigger_message_sid();

    // Traps only affect the creature on the exact tile (the creature passed
    // as an argument to this function).
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(trigger_message_sid));
    manager.send();

    trap->set_triggered(true);
  }

  return true;
}


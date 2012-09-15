#include <boost/make_shared.hpp>
#include "CommandFactory.hpp"
#include "CommandKeys.hpp"
#include "Commands.hpp"

using namespace std;
using boost::make_shared;

CommandFactory::CommandFactory()
{
}

CommandFactory::~CommandFactory()
{
}

CommandPtr CommandFactory::create(const int key, const string& command_name)
{
  CommandPtr command;

  if (command_name == CommandKeys::QUIT)
  {
    command = make_shared<QuitCommand>();
  }
  else if (command_name == CommandKeys::VERSION)
  {
    command = make_shared<VersionCommand>();
  }
  else if (command_name == CommandKeys::GAME_DATE_TIME)
  {
    command = make_shared<GameDateTimeCommand>();
  }
  else if (command_name == CommandKeys::MOVE_NORTHEAST)
  {
    command = make_shared<MovementCommand>(DIRECTION_NORTH_EAST);
  }
  else if (command_name == CommandKeys::MOVE_NORTH)
  {
    command = make_shared<MovementCommand>(DIRECTION_NORTH);
  }
  else if (command_name == CommandKeys::MOVE_NORTHWEST)
  {
    command = make_shared<MovementCommand>(DIRECTION_NORTH_WEST);
  }
  else if (command_name == CommandKeys::MOVE_EAST)
  {
    command = make_shared<MovementCommand>(DIRECTION_EAST);
  }
  else if (command_name == CommandKeys::SEARCH)
  {
    command = make_shared<SearchCommand>();
  }
  else if (command_name == CommandKeys::MOVE_WEST)
  {
    command = make_shared<MovementCommand>(DIRECTION_WEST);
  }
  else if (command_name == CommandKeys::MOVE_SOUTHEAST)
  {
    command = make_shared<MovementCommand>(DIRECTION_SOUTH_EAST);
  }
  else if (command_name == CommandKeys::MOVE_SOUTH)
  {
    command = make_shared<MovementCommand>(DIRECTION_SOUTH);
  }
  else if (command_name == CommandKeys::MOVE_SOUTHWEST)
  {
    command = make_shared<MovementCommand>(DIRECTION_SOUTH_WEST);
  }
  else if (command_name == CommandKeys::MOVE_UP)
  {
    command = make_shared<MoveUpLevelCommand>();
  }
  else if (command_name == CommandKeys::MOVE_DOWN)
  {
    command = make_shared<MoveDownLevelCommand>();
  }
  else if (command_name == CommandKeys::PICK_UP_ITEM)
  {
    command = make_shared<PickUpCommand>();
  }
  else if (command_name == CommandKeys::DROP_ITEM)
  {
    command = make_shared<DropCommand>();
  }
  else if (command_name == CommandKeys::CHAR_DUMP)
  {
    command = make_shared<CharDumpCommand>();
  }
  else if (command_name == CommandKeys::INVENTORY)
  {
    command = make_shared<InventoryCommand>();
  }
  else if (command_name == CommandKeys::PRAY)
  {
    command = make_shared<PrayCommand>();
  }
  else if (command_name == CommandKeys::MELEE_WEAPON_INFO)
  {
    command = make_shared<MeleeWeaponInfoCommand>();
  }
  else if (command_name == CommandKeys::RANGED_WEAPON_INFO)
  {
    command = make_shared<RangedWeaponInfoCommand>();
  }
  else if (command_name == CommandKeys::SELECT_TILE)
  {
    command = make_shared<SelectTileCommand>();
  }
  else if (command_name == CommandKeys::FIRE_MISSILE)
  {
    command = make_shared<FireMissileCommand>();
  }
  else if (command_name == CommandKeys::QUAFF)
  {
    command = make_shared<QuaffCommand>();
  }
  else if (command_name == CommandKeys::READ)
  {
    command = make_shared<ReadCommand>();
  }
  else if (command_name == CommandKeys::CHECK_CURRENCY)
  {
    command = make_shared<CheckCurrencyCommand>();
  }

  return command;
}

CommandFactoryType CommandFactory::get_factory_type() const
{
  return COMMAND_FACTORY_TYPE_MAP;
}

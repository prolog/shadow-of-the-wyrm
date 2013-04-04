#include <boost/make_shared.hpp>
#include "CommandFactory.hpp"
#include "CommandKeys.hpp"
#include "Commands.hpp"

using namespace std;

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
    command = boost::make_shared<QuitCommand>();
  }
  else if (command_name == CommandKeys::VERSION)
  {
    command = boost::make_shared<VersionCommand>();
  }
  else if (command_name == CommandKeys::GAME_DATE_TIME)
  {
    command = boost::make_shared<GameDateTimeCommand>();
  }
  else if (command_name == CommandKeys::MOVE_NORTHEAST)
  {
    command = boost::make_shared<MovementCommand>(DIRECTION_NORTH_EAST);
  }
  else if (command_name == CommandKeys::MOVE_NORTH)
  {
    command = boost::make_shared<MovementCommand>(DIRECTION_NORTH);
  }
  else if (command_name == CommandKeys::MOVE_NORTHWEST)
  {
    command = boost::make_shared<MovementCommand>(DIRECTION_NORTH_WEST);
  }
  else if (command_name == CommandKeys::MOVE_EAST)
  {
    command = boost::make_shared<MovementCommand>(DIRECTION_EAST);
  }
  else if (command_name == CommandKeys::SEARCH)
  {
    command = boost::make_shared<SearchCommand>();
  }
  else if (command_name == CommandKeys::MOVE_WEST)
  {
    command = boost::make_shared<MovementCommand>(DIRECTION_WEST);
  }
  else if (command_name == CommandKeys::MOVE_SOUTHEAST)
  {
    command = boost::make_shared<MovementCommand>(DIRECTION_SOUTH_EAST);
  }
  else if (command_name == CommandKeys::MOVE_SOUTH)
  {
    command = boost::make_shared<MovementCommand>(DIRECTION_SOUTH);
  }
  else if (command_name == CommandKeys::MOVE_SOUTHWEST)
  {
    command = boost::make_shared<MovementCommand>(DIRECTION_SOUTH_WEST);
  }
  else if (command_name == CommandKeys::MOVE_UP)
  {
    command = boost::make_shared<MoveUpLevelCommand>();
  }
  else if (command_name == CommandKeys::MOVE_DOWN)
  {
    command = boost::make_shared<MoveDownLevelCommand>();
  }
  else if (command_name == CommandKeys::PICK_UP_ITEM)
  {
    command = boost::make_shared<PickUpCommand>();
  }
  else if (command_name == CommandKeys::DROP_ITEM)
  {
    command = boost::make_shared<DropCommand>();
  }
  else if (command_name == CommandKeys::CHAR_DUMP)
  {
    command = boost::make_shared<CharDumpCommand>();
  }
  else if (command_name == CommandKeys::INVENTORY)
  {
    command = boost::make_shared<InventoryCommand>();
  }
  else if (command_name == CommandKeys::PRAY)
  {
    command = boost::make_shared<PrayCommand>();
  }
  else if (command_name == CommandKeys::MELEE_WEAPON_INFO)
  {
    command = boost::make_shared<MeleeWeaponInfoCommand>();
  }
  else if (command_name == CommandKeys::RANGED_WEAPON_INFO)
  {
    command = boost::make_shared<RangedWeaponInfoCommand>();
  }
  else if (command_name == CommandKeys::SELECT_TILE)
  {
    command = boost::make_shared<SelectTileCommand>();
  }
  else if (command_name == CommandKeys::FIRE_MISSILE)
  {
    command = boost::make_shared<FireMissileCommand>();
  }
  else if (command_name == CommandKeys::QUAFF)
  {
    command = boost::make_shared<QuaffCommand>();
  }
  else if (command_name == CommandKeys::READ)
  {
    command = boost::make_shared<ReadCommand>();
  }
  else if (command_name == CommandKeys::CHECK_CURRENCY)
  {
    command = boost::make_shared<CheckCurrencyCommand>();
  }
  else if (command_name == CommandKeys::SAVE_GAME)
  {
    command = boost::make_shared<SaveGameCommand>();
  }
  else if (command_name == CommandKeys::EAT)
  {
    command = boost::make_shared<EatCommand>();
  }
  else if (command_name == CommandKeys::CHAT)
  {
    command = boost::make_shared<ChatCommand>();
  }
  else if (command_name == CommandKeys::APPLY_FEATURE)
  {
    command = boost::make_shared<ApplyFeatureCommand>();
  }
  else if (command_name == CommandKeys::QUEST_LIST)
  {
    command = boost::make_shared<QuestListCommand>();
  }
  else if (command_name == CommandKeys::RELOAD_SCRIPTS_AND_SIDS)
  {
    command = boost::make_shared<ReloadScriptsCommand>();
  }
  else if (command_name == CommandKeys::RUN_SCRIPT)
  {
    command = boost::make_shared<RunScriptCommand>();
  }
  else if (command_name == CommandKeys::CAST_SPELL)
  {
    command = boost::make_shared<CastSpellCommand>();
  }

  return command;
}

CommandFactoryType CommandFactory::get_factory_type() const
{
  return COMMAND_FACTORY_TYPE_MAP;
}

CommandFactory* CommandFactory::clone()
{
  return new CommandFactory(*this);
}

// Save/load.
bool CommandFactory::serialize(std::ostream& stream)
{
  return true;
}

bool CommandFactory::deserialize(std::istream& stream)
{
  return true;
}

ClassIdentifier CommandFactory::internal_class_identifier() const
{
  return CLASS_ID_COMMAND_FACTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/CommandFactory_test.cpp"
#endif
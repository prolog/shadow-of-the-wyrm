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
    command = std::make_shared<QuitCommand>();
  }
  else if (command_name == CommandKeys::VERSION)
  {
    command = std::make_shared<VersionCommand>();
  }
  else if (command_name == CommandKeys::GAME_DATE_TIME)
  {
    command = std::make_shared<GameDateTimeCommand>();
  }
  else if (command_name == CommandKeys::MOVE_NORTHEAST)
  {
    command = std::make_shared<MovementCommand>(DIRECTION_NORTH_EAST);
  }
  else if (command_name == CommandKeys::MOVE_NORTH)
  {
    command = std::make_shared<MovementCommand>(DIRECTION_NORTH);
  }
  else if (command_name == CommandKeys::MOVE_NORTHWEST)
  {
    command = std::make_shared<MovementCommand>(DIRECTION_NORTH_WEST);
  }
  else if (command_name == CommandKeys::MOVE_EAST)
  {
    command = std::make_shared<MovementCommand>(DIRECTION_EAST);
  }
  else if (command_name == CommandKeys::SEARCH)
  {
    command = std::make_shared<SearchCommand>();
  }
  else if (command_name == CommandKeys::MOVE_WEST)
  {
    command = std::make_shared<MovementCommand>(DIRECTION_WEST);
  }
  else if (command_name == CommandKeys::MOVE_SOUTHEAST)
  {
    command = std::make_shared<MovementCommand>(DIRECTION_SOUTH_EAST);
  }
  else if (command_name == CommandKeys::MOVE_SOUTH)
  {
    command = std::make_shared<MovementCommand>(DIRECTION_SOUTH);
  }
  else if (command_name == CommandKeys::MOVE_SOUTHWEST)
  {
    command = std::make_shared<MovementCommand>(DIRECTION_SOUTH_WEST);
  }
  else if (command_name == CommandKeys::MOVE_UP)
  {
    command = std::make_shared<MoveUpLevelCommand>();
  }
  else if (command_name == CommandKeys::MOVE_DOWN)
  {
    command = std::make_shared<MoveDownLevelCommand>();
  }
  else if (command_name == CommandKeys::AUTOMATIC_MOVEMENT)
  {
    command = std::make_shared<AutomaticMovementCommand>();
  }
  else if (command_name == CommandKeys::PICK_UP_ITEM)
  {
    command = std::make_shared<PickUpCommand>();
  }
  else if (command_name == CommandKeys::DROP_ITEM)
  {
    command = std::make_shared<DropCommand>();
  }
  else if (command_name == CommandKeys::CHAR_DUMP)
  {
    command = std::make_shared<CharDumpCommand>();
  }
  else if (command_name == CommandKeys::INVENTORY)
  {
    command = std::make_shared<InventoryCommand>();
  }
  else if (command_name == CommandKeys::PRAY)
  {
    command = std::make_shared<PrayCommand>();
  }
  else if (command_name == CommandKeys::MELEE_WEAPON_INFO)
  {
    command = std::make_shared<MeleeWeaponInfoCommand>();
  }
  else if (command_name == CommandKeys::RANGED_WEAPON_INFO)
  {
    command = std::make_shared<RangedWeaponInfoCommand>();
  }
  else if (command_name == CommandKeys::SELECT_TILE)
  {
    command = std::make_shared<SelectTileCommand>();
  }
  else if (command_name == CommandKeys::FIRE_MISSILE)
  {
    command = std::make_shared<FireMissileCommand>();
  }
  else if (command_name == CommandKeys::QUAFF)
  {
    command = std::make_shared<QuaffCommand>();
  }
  else if (command_name == CommandKeys::READ)
  {
    command = std::make_shared<ReadCommand>();
  }
  else if (command_name == CommandKeys::CHECK_CURRENCY)
  {
    command = std::make_shared<CheckCurrencyCommand>();
  }
  else if (command_name == CommandKeys::SAVE_GAME)
  {
    command = std::make_shared<SaveGameCommand>();
  }
  else if (command_name == CommandKeys::EAT)
  {
    command = std::make_shared<EatCommand>();
  }
  else if (command_name == CommandKeys::CHAT)
  {
    command = std::make_shared<ChatCommand>();
  }
  else if (command_name == CommandKeys::APPLY_FEATURE)
  {
    command = std::make_shared<ApplyFeatureCommand>();
  }
  else if (command_name == CommandKeys::QUEST_LIST)
  {
    command = std::make_shared<QuestListCommand>();
  }
  else if (command_name == CommandKeys::RELOAD_SCRIPTS_AND_SIDS)
  {
    command = std::make_shared<ReloadScriptsCommand>();
  }
  else if (command_name == CommandKeys::RUN_SCRIPT)
  {
    command = std::make_shared<RunScriptCommand>();
  }
  else if (command_name == CommandKeys::CAST_SPELL)
  {
    command = std::make_shared<CastSpellCommand>();
  }
  else if (command_name == CommandKeys::BESTIARY)
  {
    command = std::make_shared<BestiaryCommand>();
  }
  else if (command_name == CommandKeys::EVOKE)
  {
    command = std::make_shared<EvokeCommand>();
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
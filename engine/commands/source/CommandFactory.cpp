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
    command = std::make_shared<QuitCommand>(key);
  }
  else if (command_name == CommandKeys::VERSION)
  {
    command = std::make_shared<VersionCommand>(key);
  }
  else if (command_name == CommandKeys::GAME_DATE_TIME)
  {
    command = std::make_shared<GameDateTimeCommand>(key);
  }
  else if (command_name == CommandKeys::MOVE_NORTHEAST)
  {
    command = std::make_shared<MovementCommand>(Direction::DIRECTION_NORTH_EAST, key);
  }
  else if (command_name == CommandKeys::MOVE_NORTH)
  {
    command = std::make_shared<MovementCommand>(Direction::DIRECTION_NORTH, key);
  }
  else if (command_name == CommandKeys::MOVE_NORTHWEST)
  {
    command = std::make_shared<MovementCommand>(Direction::DIRECTION_NORTH_WEST, key);
  }
  else if (command_name == CommandKeys::MOVE_EAST)
  {
    command = std::make_shared<MovementCommand>(Direction::DIRECTION_EAST, key);
  }
  else if (command_name == CommandKeys::SEARCH)
  {
    command = std::make_shared<SearchCommand>(key);
  }
  else if (command_name == CommandKeys::MOVE_WEST)
  {
    command = std::make_shared<MovementCommand>(Direction::DIRECTION_WEST, key);
  }
  else if (command_name == CommandKeys::MOVE_SOUTHEAST)
  {
    command = std::make_shared<MovementCommand>(Direction::DIRECTION_SOUTH_EAST, key);
  }
  else if (command_name == CommandKeys::MOVE_SOUTH)
  {
    command = std::make_shared<MovementCommand>(Direction::DIRECTION_SOUTH, key);
  }
  else if (command_name == CommandKeys::MOVE_SOUTHWEST)
  {
    command = std::make_shared<MovementCommand>(Direction::DIRECTION_SOUTH_WEST, key);
  }
  else if (command_name == CommandKeys::MOVE_UP)
  {
    command = std::make_shared<MoveUpLevelCommand>(key);
  }
  else if (command_name == CommandKeys::MOVE_DOWN)
  {
    command = std::make_shared<MoveDownLevelCommand>(key);
  }
  else if (command_name == CommandKeys::AUTOMATIC_MOVEMENT)
  {
    command = std::make_shared<AutomaticMovementCommand>(key);
  }
  else if (command_name == CommandKeys::PICK_UP_ITEM)
  {
    command = std::make_shared<PickUpCommand>(key);
  }
  else if (command_name == CommandKeys::DROP_ITEM)
  {
    command = std::make_shared<DropCommand>(key);
  }
  else if (command_name == CommandKeys::CHAR_DUMP)
  {
    command = std::make_shared<CharDumpCommand>(key);
  }
  else if (command_name == CommandKeys::INVENTORY)
  {
    command = std::make_shared<InventoryCommand>(key);
  }
  else if (command_name == CommandKeys::PRAY)
  {
    command = std::make_shared<PrayCommand>(key);
  }
  else if (command_name == CommandKeys::MELEE_WEAPON_INFO)
  {
    command = std::make_shared<MeleeWeaponInfoCommand>(key);
  }
  else if (command_name == CommandKeys::RANGED_WEAPON_INFO)
  {
    command = std::make_shared<RangedWeaponInfoCommand>(key);
  }
  else if (command_name == CommandKeys::SELECT_TILE)
  {
    command = std::make_shared<SelectTileCommand>(key);
  }
  else if (command_name == CommandKeys::FIRE_MISSILE)
  {
    command = std::make_shared<FireMissileCommand>(key);
  }
  else if (command_name == CommandKeys::QUAFF)
  {
    command = std::make_shared<QuaffCommand>(key);
  }
  else if (command_name == CommandKeys::READ)
  {
    command = std::make_shared<ReadCommand>(key);
  }
  else if (command_name == CommandKeys::CHECK_CURRENCY)
  {
    command = std::make_shared<CheckCurrencyCommand>(key);
  }
  else if (command_name == CommandKeys::SAVE_GAME)
  {
    command = std::make_shared<SaveGameCommand>(key);
  }
  else if (command_name == CommandKeys::EAT)
  {
    command = std::make_shared<EatCommand>(key);
  }
  else if (command_name == CommandKeys::CHAT)
  {
    command = std::make_shared<ChatCommand>(key);
  }
  else if (command_name == CommandKeys::APPLY_FEATURE)
  {
    command = std::make_shared<ApplyFeatureCommand>(key);
  }
  else if (command_name == CommandKeys::QUEST_LIST)
  {
    command = std::make_shared<QuestListCommand>(key);
  }
  else if (command_name == CommandKeys::RELOAD_SCRIPTS_AND_SIDS)
  {
    command = std::make_shared<ReloadScriptsCommand>(key);
  }
  else if (command_name == CommandKeys::RUN_SCRIPT)
  {
    command = std::make_shared<RunScriptCommand>(key);
  }
  else if (command_name == CommandKeys::CAST_SPELL)
  {
    command = std::make_shared<CastSpellCommand>(key);
  }
  else if (command_name == CommandKeys::BESTIARY)
  {
    command = std::make_shared<BestiaryCommand>(key);
  }
  else if (command_name == CommandKeys::EVOKE)
  {
    command = std::make_shared<EvokeCommand>(key);
  }
  else if (command_name == CommandKeys::SHOW_RESISTANCES)
  {
    command = std::make_shared<ShowResistancesCommand>(key);
  }
  else if (command_name == CommandKeys::SHOW_CONDUCTS)
  {
    command = std::make_shared<ShowConductsCommand>(key);
  }
  else if (command_name == CommandKeys::LATEST_MESSAGES)
  {
    command = std::make_shared<LatestMessagesCommand>(key);
  }
  else if (command_name == CommandKeys::KICK)
  {
    command = std::make_shared<KickCommand>(key);
  }
  else if (command_name == CommandKeys::OFFER)
  {
    command = std::make_shared<OfferCommand>(key);
  }
  else if (command_name == CommandKeys::SKIN)
  {
    command = std::make_shared<SkinCommand>(key);
  }

  return command;
}

CommandFactoryType CommandFactory::get_factory_type() const
{
  return CommandFactoryType::COMMAND_FACTORY_TYPE_MAP;
}

CommandFactory* CommandFactory::clone()
{
  return new CommandFactory(*this);
}

// Save/load.
bool CommandFactory::serialize(std::ostream& stream) const
{
  return true;
}

bool CommandFactory::deserialize(std::istream& stream)
{
  return true;
}

ClassIdentifier CommandFactory::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_COMMAND_FACTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/CommandFactory_test.cpp"
#endif
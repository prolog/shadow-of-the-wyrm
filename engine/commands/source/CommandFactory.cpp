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

// Omitted: the custom script command, which gets instantiated
// only through the AI process, and is not a keyboard-based command.
CommandPtr CommandFactory::create(const int key, const string& command_name)
{
  CommandPtr command;

  if (command_name == CommandKeys::QUIT)
  {
    command = std::make_unique<QuitCommand>(key);
  }
  else if (command_name == CommandKeys::VERSION)
  {
    command = std::make_unique<VersionCommand>(key);
  }
  else if (command_name == CommandKeys::GAME_DATE_TIME_WEATHER)
  {
    command = std::make_unique<GameDateTimeWeatherCommand>(key);
  }
  else if (command_name == CommandKeys::MOVE_NORTHEAST)
  {
    command = std::make_unique<MovementCommand>(Direction::DIRECTION_NORTH_EAST, key);
  }
  else if (command_name == CommandKeys::MOVE_NORTH)
  {
    command = std::make_unique<MovementCommand>(Direction::DIRECTION_NORTH, key);
  }
  else if (command_name == CommandKeys::MOVE_NORTHWEST)
  {
    command = std::make_unique<MovementCommand>(Direction::DIRECTION_NORTH_WEST, key);
  }
  else if (command_name == CommandKeys::MOVE_EAST)
  {
    command = std::make_unique<MovementCommand>(Direction::DIRECTION_EAST, key);
  }
  else if (command_name == CommandKeys::SEARCH)
  {
    command = std::make_unique<SearchCommand>(key);
  }
  else if (command_name == CommandKeys::MOVE_WEST)
  {
    command = std::make_unique<MovementCommand>(Direction::DIRECTION_WEST, key);
  }
  else if (command_name == CommandKeys::MOVE_SOUTHEAST)
  {
    command = std::make_unique<MovementCommand>(Direction::DIRECTION_SOUTH_EAST, key);
  }
  else if (command_name == CommandKeys::MOVE_SOUTH)
  {
    command = std::make_unique<MovementCommand>(Direction::DIRECTION_SOUTH, key);
  }
  else if (command_name == CommandKeys::MOVE_SOUTHWEST)
  {
    command = std::make_unique<MovementCommand>(Direction::DIRECTION_SOUTH_WEST, key);
  }
  else if (command_name == CommandKeys::MOVE_UP)
  {
    command = std::make_unique<MoveUpLevelCommand>(key);
  }
  else if (command_name == CommandKeys::MOVE_DOWN)
  {
    command = std::make_unique<MoveDownLevelCommand>(key);
  }
  else if (command_name == CommandKeys::AUTOMATIC_MOVEMENT)
  {
    command = std::make_unique<AutomaticMovementCommand>(key);
  }
  else if (command_name == CommandKeys::PICK_UP_ITEM)
  {
    command = std::make_unique<PickUpCommand>(key);
  }
  else if (command_name == CommandKeys::PICK_UP_ALL)
  {
    command = std::make_unique<PickUpAllCommand>(key);
  }
  else if (command_name == CommandKeys::DROP_ITEM)
  {
    command = std::make_unique<DropCommand>(key);
  }
  else if (command_name == CommandKeys::CHAR_DETAILS)
  {
    command = std::make_unique<CharDetailsCommand>(key);
  }
  else if (command_name == CommandKeys::CHAR_DUMP)
  {
    command = std::make_unique<CharDumpCommand>(key);
  }
  else if (command_name == CommandKeys::INVENTORY)
  {
    command = std::make_unique<InventoryCommand>(key);
  }
  else if (command_name == CommandKeys::PRAY)
  {
    command = std::make_unique<PrayCommand>(key);
  }
  else if (command_name == CommandKeys::MELEE_WEAPON_INFO)
  {
    command = std::make_unique<MeleeWeaponInfoCommand>(key);
  }
  else if (command_name == CommandKeys::RANGED_WEAPON_INFO)
  {
    command = std::make_unique<RangedWeaponInfoCommand>(key);
  }
  else if (command_name == CommandKeys::SELECT_TILE)
  {
    command = std::make_unique<SelectTileCommand>(key);
  }
  else if (command_name == CommandKeys::FIRE_MISSILE)
  {
    command = std::make_unique<FireMissileCommand>(key);
  }
  else if (command_name == CommandKeys::QUAFF)
  {
    command = std::make_unique<QuaffCommand>(key);
  }
  else if (command_name == CommandKeys::READ)
  {
    command = std::make_unique<ReadCommand>(key);
  }
  else if (command_name == CommandKeys::CHECK_CURRENCY)
  {
    command = std::make_unique<CheckCurrencyCommand>(key);
  }
  else if (command_name == CommandKeys::SAVE_GAME)
  {
    command = std::make_unique<SaveGameCommand>(key);
  }
  else if (command_name == CommandKeys::EAT)
  {
    command = std::make_unique<EatCommand>(key);
  }
  else if (command_name == CommandKeys::CHAT)
  {
    command = std::make_unique<ChatCommand>(key);
  }
  else if (command_name == CommandKeys::APPLY_FEATURE)
  {
    command = std::make_unique<ApplyFeatureCommand>(key);
  }
  else if (command_name == CommandKeys::QUEST_LIST)
  {
    command = std::make_unique<QuestListCommand>(key);
  }
  else if (command_name == CommandKeys::RELOAD_SCRIPTS_TEXTURES_AND_SIDS)
  {
    command = std::make_unique<ReloadScriptsCommand>(key);
  }
  else if (command_name == CommandKeys::RUN_SCRIPT)
  {
    command = std::make_unique<RunScriptCommand>(key);
  }
  else if (command_name == CommandKeys::CAST_SPELL)
  {
    command = std::make_unique<CastSpellCommand>(key);
  }
  else if (command_name == CommandKeys::BESTIARY)
  {
    command = std::make_unique<BestiaryCommand>(key);
  }
  else if (command_name == CommandKeys::EVOKE)
  {
    command = std::make_unique<EvokeCommand>(key);
  }
  else if (command_name == CommandKeys::SHOW_RESISTANCES)
  {
    command = std::make_unique<ShowResistancesCommand>(key);
  }
  else if (command_name == CommandKeys::SHOW_CONDUCTS)
  {
    command = std::make_unique<ShowConductsCommand>(key);
  }
  else if (command_name == CommandKeys::SHOW_SKILLS)
  {
    command = std::make_unique<ShowSkillsCommand>(key);
  }
  else if (command_name == CommandKeys::LATEST_MESSAGES)
  {
    command = std::make_unique<LatestMessagesCommand>(key);
  }
  else if (command_name == CommandKeys::KICK)
  {
    command = std::make_unique<KickCommand>(key);
  }
  else if (command_name == CommandKeys::OFFER)
  {
    command = std::make_unique<OfferCommand>(key);
  }
  else if (command_name == CommandKeys::SKIN)
  {
    command = std::make_unique<SkinCommand>(key);
  }
  else if (command_name == CommandKeys::PIETY)
  {
    command = std::make_unique<PietyCommand>(key);
  }
  else if (command_name == CommandKeys::EXPERIENCE)
  {
    command = std::make_unique<ExperienceCommand>(key);
  }
  else if (command_name == CommandKeys::REST)
  {
    command = std::make_unique<RestCommand>(key);
  }
  else if (command_name == CommandKeys::VIEW_ITEMS)
  {
    command = std::make_unique<ViewItemsCommand>(key);
  }
  else if (command_name == CommandKeys::HELP)
  {
    command = std::make_unique<HelpCommand>(key);
  }
  else if (command_name == CommandKeys::INSCRIBE)
  {
    command = std::make_unique<InscribeCommand>(key);
  }
  else if (command_name == CommandKeys::TOGGLE_AUTOPICKUP)
  {
    command = std::make_unique<ToggleAutopickupCommand>(key);
  }
  else if (command_name == CommandKeys::BREED)
  {
    command = std::make_unique<BreedCommand>(key);
  }
  else if (command_name == CommandKeys::ITEM_CODEX)
  {
    command = std::make_unique<ItemCodexCommand>(key);
  }
  else if (command_name == CommandKeys::SWITCH_GRAPHICS_MODE)
  {
    command = std::make_unique<SwitchGraphicsModeCommand>(key);
  }
  else if (command_name == CommandKeys::SWITCH_COLOUR_PALETTES)
  {
    command = std::make_unique<SwitchColourPalettesCommand>(key);
  }
  else if (command_name == CommandKeys::ORDER)
  {
    command = std::make_unique<OrderCommand>(key);
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
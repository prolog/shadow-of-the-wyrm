#include "Commands.hpp"
#include "CommandKeys.hpp"
#include "Conversion.hpp"
#include "StringConstants.hpp"

using namespace std;

// Quit
QuitCommand::QuitCommand()
: Command(CommandKeys::QUIT, TextKeys::DECISION_QUIT_GAME)
{
}

QuitCommand::~QuitCommand()
{
}

// Version
VersionCommand::VersionCommand()
: Command(CommandKeys::VERSION)
{
}

VersionCommand::~VersionCommand()
{
}

// Date/Time
GameDateTimeCommand::GameDateTimeCommand()
: Command(CommandKeys::GAME_DATE_TIME)
{
}

GameDateTimeCommand::~GameDateTimeCommand()
{
}

// Directional
DirectionalCommand::DirectionalCommand(const Direction d)
: Command("") // This will be a no-op command, since the command key is empty.
, direction(d)
{
}

DirectionalCommand::~DirectionalCommand()
{
}

Direction DirectionalCommand::get_direction() const
{
  return direction;
}

bool DirectionalCommand::requires_confirmation() const
{
  return false; // This'll be determined by the movement manager.
}

// Movement
MovementCommand::MovementCommand(const Direction d)
: DirectionalCommand(d)
{
  // Get the direction CommandKey based on the Direction enum
  string name  = DirectionEnum::to_string(direction);
  command_name = name;
}

MovementCommand::~MovementCommand()
{
}

// Move up or down a level
MoveUpLevelCommand::MoveUpLevelCommand()
: Command(CommandKeys::MOVE_UP)
{
}

MoveUpLevelCommand::~MoveUpLevelCommand()
{
}

MoveDownLevelCommand::MoveDownLevelCommand()
: Command(CommandKeys::MOVE_DOWN)
{
}

MoveDownLevelCommand::~MoveDownLevelCommand()
{
}

// Attack
AttackCommand::AttackCommand(const Direction d)
: DirectionalCommand(d)
{
  string name  = DirectionEnum::to_attack_string(d);
  command_name = name;
}

AttackCommand::~AttackCommand()
{
}

// Search
SearchCommand::SearchCommand()
: Command(CommandKeys::SEARCH)
{
}

SearchCommand::~SearchCommand()
{
}

// Pray
PrayCommand::PrayCommand()
: Command(CommandKeys::PRAY)
{
}

PrayCommand::~PrayCommand()
{
}

// Pick up
PickUpCommand::PickUpCommand()
: Command(CommandKeys::PICK_UP_ITEM)
{
}

PickUpCommand::~PickUpCommand()
{
}

// Drop
DropCommand::DropCommand()
: Command(CommandKeys::DROP_ITEM)
{
}

DropCommand::~DropCommand()
{
}

// Dump (pretty-print) the character to a file
CharDumpCommand::CharDumpCommand()
: Command(CommandKeys::CHAR_DUMP)
{
}

CharDumpCommand::~CharDumpCommand()
{
}

// Equipment and Inventory management
InventoryCommand::InventoryCommand()
: Command(CommandKeys::INVENTORY)
{
}

InventoryCommand::~InventoryCommand()
{
}

// Melee and ranged weapon info commands
MeleeWeaponInfoCommand::MeleeWeaponInfoCommand()
: Command(CommandKeys::MELEE_WEAPON_INFO)
{
}

MeleeWeaponInfoCommand::~MeleeWeaponInfoCommand()
{
}

RangedWeaponInfoCommand::RangedWeaponInfoCommand()
: Command(CommandKeys::RANGED_WEAPON_INFO)
{
}

RangedWeaponInfoCommand::~RangedWeaponInfoCommand()
{
}

// Select Tile (aka, "Look")
SelectTileCommand::SelectTileCommand()
: Command(CommandKeys::SELECT_TILE)
{
}

SelectTileCommand::~SelectTileCommand()
{
}

// Fire currently-equipped Ammunition
FireMissileCommand::FireMissileCommand()
: Command(CommandKeys::FIRE_MISSILE)
{
}

FireMissileCommand::~FireMissileCommand()
{
}

// 'q'uaff a potion
QuaffCommand::QuaffCommand()
: Command(CommandKeys::QUAFF)
{
}

QuaffCommand::~QuaffCommand()
{
}

// 'r'ead a scroll or spellbook
ReadCommand::ReadCommand()
: Command(CommandKeys::READ)
{
}

ReadCommand::~ReadCommand()
{
}

// '$': check how much currency is currently held
CheckCurrencyCommand::CheckCurrencyCommand()
: Command(CommandKeys::CHECK_CURRENCY)
{
}

CheckCurrencyCommand::~CheckCurrencyCommand()
{
}

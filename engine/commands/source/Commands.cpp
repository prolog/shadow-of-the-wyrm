#include "Commands.hpp"
#include "CommandKeys.hpp"
#include "EngineConversion.hpp"
#include "TextKeys.hpp"

using namespace std;

// Quit
QuitCommand::QuitCommand(const int key)
: Command(CommandKeys::QUIT, key, TextKeys::DECISION_QUIT_GAME)
{
}

QuitCommand::~QuitCommand()
{
}

// Version
VersionCommand::VersionCommand(const int key)
: Command(CommandKeys::VERSION, key)
{
}

VersionCommand::~VersionCommand()
{
}

// Date/Time/Weather
GameDateTimeWeatherCommand::GameDateTimeWeatherCommand(const int key)
: Command(CommandKeys::GAME_DATE_TIME_WEATHER, key)
{
}

GameDateTimeWeatherCommand::~GameDateTimeWeatherCommand()
{
}

// Directional
DirectionalCommand::DirectionalCommand(const Direction d, const int key)
: Command("", key) // This will be a no-op command, since the command key is empty.
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
MovementCommand::MovementCommand(const Direction d, const int key)
: DirectionalCommand(d, key)
{
  // Get the direction CommandKey based on the Direction enum
  string name  = DirectionEnum::to_string(direction);
  command_name = name;
}

MovementCommand::~MovementCommand()
{
}

bool MovementCommand::get_allow_clear_message_buffer() const
{
  return (key_pressed != -1);
}

// Move up or down a level
MoveUpLevelCommand::MoveUpLevelCommand(const int key)
: Command(CommandKeys::MOVE_UP, key)
{
}

MoveUpLevelCommand::~MoveUpLevelCommand()
{
}

MoveDownLevelCommand::MoveDownLevelCommand(const int key)
: Command(CommandKeys::MOVE_DOWN, key)
{
}

MoveDownLevelCommand::~MoveDownLevelCommand()
{
}

// Automatic movement (a.k.a. "run")
AutomaticMovementCommand::AutomaticMovementCommand(const int key)
: Command(CommandKeys::AUTOMATIC_MOVEMENT, key)
{
}

AutomaticMovementCommand::~AutomaticMovementCommand()
{
}

bool AutomaticMovementCommand::get_allow_clear_message_buffer() const
{
  return false;
}

// Attack
AttackCommand::AttackCommand(const Direction d, const int key)
: DirectionalCommand(d, key)
{
  command_name = DirectionEnum::to_attack_string(d);
}

AttackCommand::~AttackCommand()
{
}

// Search
SearchCommand::SearchCommand(const int key)
: MovementCommand(Direction::DIRECTION_NULL, key)
{
}

SearchCommand::~SearchCommand()
{
}

// Pray
PrayCommand::PrayCommand(const int key)
: Command(CommandKeys::PRAY, key)
{
}

PrayCommand::~PrayCommand()
{
}

// Pick up
PickUpCommand::PickUpCommand(const int key)
: Command(CommandKeys::PICK_UP_ITEM, key)
{
}

PickUpCommand::PickUpCommand(const string& new_item_id)
: Command(CommandKeys::PICK_UP_ITEM, '?'), item_id(new_item_id)
{
}

PickUpCommand::~PickUpCommand()
{
}

string PickUpCommand::get_item_id() const
{
  return item_id;
}

// Pick up all

PickUpAllCommand::PickUpAllCommand(const int key)
: Command(CommandKeys::PICK_UP_ALL, key)
{
}

PickUpAllCommand::~PickUpAllCommand()
{
}

// Drop
DropCommand::DropCommand(const int key)
: Command(CommandKeys::DROP_ITEM, key)
{
}

DropCommand::DropCommand(const string& new_drop_id)
: Command(CommandKeys::DROP_ITEM, '?'), drop_id(new_drop_id)
{
}

DropCommand::~DropCommand()
{
}

string DropCommand::get_drop_id() const
{
  return drop_id;
}

// Display character details
CharDetailsCommand::CharDetailsCommand(const int key)
: Command(CommandKeys::CHAR_DETAILS, key)
{
}

CharDetailsCommand::~CharDetailsCommand()
{
}

// Dump (pretty-print) the character to a file
CharDumpCommand::CharDumpCommand(const int key)
: Command(CommandKeys::CHAR_DUMP, key)
{
}

CharDumpCommand::~CharDumpCommand()
{
}

// Equipment and Inventory management
InventoryCommand::InventoryCommand(const int key)
: Command(CommandKeys::INVENTORY, key), ewl(EquipmentWornLocation::EQUIPMENT_WORN_NONE)
{
}

InventoryCommand::InventoryCommand(const EquipmentWornLocation new_ewl, ItemPtr new_item)
: Command(CommandKeys::INVENTORY, '?'), ewl(new_ewl), i(new_item)
{
}

InventoryCommand::~InventoryCommand()
{
}

EquipmentWornLocation InventoryCommand::get_equipment_worn_location() const
{
  return ewl;
}

ItemPtr InventoryCommand::get_item()
{
  return i;
}

// Melee and ranged weapon info commands
MeleeWeaponInfoCommand::MeleeWeaponInfoCommand(const int key)
: Command(CommandKeys::MELEE_WEAPON_INFO, key)
{
}

MeleeWeaponInfoCommand::~MeleeWeaponInfoCommand()
{
}

RangedWeaponInfoCommand::RangedWeaponInfoCommand(const int key)
: Command(CommandKeys::RANGED_WEAPON_INFO, key)
{
}

RangedWeaponInfoCommand::~RangedWeaponInfoCommand()
{
}

// Select Tile (aka, "Look")
SelectTileCommand::SelectTileCommand(const int key)
: Command(CommandKeys::SELECT_TILE, key)
{
}

SelectTileCommand::~SelectTileCommand()
{
}

// Fire currently-equipped Ammunition
FireMissileCommand::FireMissileCommand(const int key)
: Command(CommandKeys::FIRE_MISSILE, key)
{
}

FireMissileCommand::~FireMissileCommand()
{
}

// 'q'uaff a potion
QuaffCommand::QuaffCommand(const int key)
: Command(CommandKeys::QUAFF, key)
{
}

QuaffCommand::~QuaffCommand()
{
}

// 'r'ead a scroll or spellbook
ReadCommand::ReadCommand(const std::string& read_item_id)
: Command(CommandKeys::READ, '?'), readable_id(read_item_id)
{
}

ReadCommand::ReadCommand(const int key)
: Command(CommandKeys::READ, key)
{
}

ReadCommand::~ReadCommand()
{
}

std::string ReadCommand::get_item_id() const
{
  return readable_id;
}

// '$': check how much currency is currently held
CheckCurrencyCommand::CheckCurrencyCommand(const int key)
: Command(CommandKeys::CHECK_CURRENCY, key)
{
}

CheckCurrencyCommand::~CheckCurrencyCommand()
{
}

// 'S'ave the game
SaveGameCommand::SaveGameCommand(const int key)
: Command(CommandKeys::SAVE_GAME, key, TextKeys::DECISION_SAVE_GAME)
{
}

SaveGameCommand::~SaveGameCommand()
{
}

// 'e'at
EatCommand::EatCommand(const int key)
: Command(CommandKeys::EAT, key)
{
}

EatCommand::~EatCommand()
{
}

// Chat with another creature
ChatCommand::ChatCommand(const int key)
: Command(CommandKeys::CHAT, key)
{
}

ChatCommand::~ChatCommand()
{
}

// Apply a terrain feature: open a door, etc.
ApplyFeatureCommand::ApplyFeatureCommand(const int key)
: Command(CommandKeys::APPLY_FEATURE, key)
{
}

ApplyFeatureCommand::~ApplyFeatureCommand()
{
}

// See the list of quests
QuestListCommand::QuestListCommand(const int key)
: Command(CommandKeys::QUEST_LIST, key)
{
}

QuestListCommand::~QuestListCommand()
{
}

// Clear the Lua state (scripts will reload)
ReloadScriptsCommand::ReloadScriptsCommand(const int key)
: Command(CommandKeys::RELOAD_SCRIPTS_TEXTURES_AND_SIDS, key)
{
}

ReloadScriptsCommand::~ReloadScriptsCommand()
{
}

// Run a Lua statement (debug mode only)
RunScriptCommand::RunScriptCommand(const int key)
: Command(CommandKeys::RUN_SCRIPT, key)
{
}

RunScriptCommand::~RunScriptCommand()
{
}

// 'z'ap (cast) a spell
CastSpellCommand::CastSpellCommand(const int key)
: Command(CommandKeys::CAST_SPELL, key)
{
}

CastSpellCommand::~CastSpellCommand()
{
}

// Beastiary (creature info)
BestiaryCommand::BestiaryCommand(const int key)
: Command(CommandKeys::BESTIARY, key)
{
}

BestiaryCommand::~BestiaryCommand()
{
}

// E'v'oke (zap) a wand
EvokeCommand::EvokeCommand(const int key)
: Command(CommandKeys::EVOKE, key), d(Direction::DIRECTION_NULL)
{
}

EvokeCommand::EvokeCommand(const string& new_item_id, const Direction new_d)
: Command(CommandKeys::EVOKE, '?'), item_id(new_item_id), d(new_d)
{
}

string EvokeCommand::get_item_id() const
{
  return item_id;
}

Direction EvokeCommand::get_direction() const
{
  return d;
}

EvokeCommand::~EvokeCommand()
{
}

// Show the player's resists and vulns
ShowResistancesCommand::ShowResistancesCommand(const int key)
: Command(CommandKeys::SHOW_RESISTANCES, key)
{
}

ShowResistancesCommand::~ShowResistancesCommand()
{
}

// Show the current conducts for the player
ShowConductsCommand::ShowConductsCommand(const int key)
: Command(CommandKeys::SHOW_CONDUCTS, key)
{
}

ShowConductsCommand::~ShowConductsCommand()
{
}

// Show the player's skills
ShowSkillsCommand::ShowSkillsCommand(const int key)
: Command(CommandKeys::SHOW_SKILLS, key)
{
}

ShowSkillsCommand::~ShowSkillsCommand()
{
}

// View the message buffer
LatestMessagesCommand::LatestMessagesCommand(const int key)
: Command(CommandKeys::LATEST_MESSAGES, key)
{
}

LatestMessagesCommand::~LatestMessagesCommand()
{
}

// Kick
KickCommand::KickCommand(const int key)
: DirectionalCommand(Direction::DIRECTION_NULL,key)
{
  command_name = CommandKeys::KICK;
}

KickCommand::KickCommand(const Direction kick_dir, const int key)
: DirectionalCommand(kick_dir, key)
{
  command_name = CommandKeys::KICK;
}

KickCommand::~KickCommand()
{
}

// Offer
OfferCommand::OfferCommand(int key)
: Command(CommandKeys::OFFER, key)
{
}

OfferCommand::~OfferCommand()
{
}

// Skin
SkinCommand::SkinCommand(int key)
: Command(CommandKeys::SKIN, key)
{
}

SkinCommand::~SkinCommand()
{
}

// Piety
PietyCommand::PietyCommand(int key)
  : Command(CommandKeys::PIETY, key)
{
}

PietyCommand::~PietyCommand()
{
}

// Experience details
ExperienceCommand::ExperienceCommand(int key)
: Command(CommandKeys::EXPERIENCE, key)
{
}

ExperienceCommand::~ExperienceCommand()
{
}

// A custom script command that uses the Lua API to interact with the
// engine
CustomScriptCommand::CustomScriptCommand()
: Command(CommandKeys::CUSTOM_SCRIPT_COMMAND, '?')
{
}

CustomScriptCommand::~CustomScriptCommand()
{
}

// Rest!
RestCommand::RestCommand(int key)
: DirectionalCommand(Direction::DIRECTION_NULL, key)
{
  command_name = CommandKeys::REST;
}

RestCommand::~RestCommand()
{
}

// View Items
ViewItemsCommand::ViewItemsCommand(int key)
: Command(CommandKeys::VIEW_ITEMS, key)
{
}

ViewItemsCommand::~ViewItemsCommand()
{
}

// View help, keybindings, etc.
HelpCommand::HelpCommand(int key)
: Command(CommandKeys::HELP, key)
{
}

HelpCommand::~HelpCommand()
{
}

// Inscribe something on the tile.
InscribeCommand::InscribeCommand(int key)
: Command(CommandKeys::INSCRIBE, key)
{
}

InscribeCommand::~InscribeCommand()
{
}

// Toggle various automatic actions
AutomaticActionsCommand::AutomaticActionsCommand(int key)
: Command(CommandKeys::AUTOMATIC_ACTIONS, key)
{
}

AutomaticActionsCommand::~AutomaticActionsCommand()
{
}

// Item codex
ItemCodexCommand::ItemCodexCommand(int key)
: Command(CommandKeys::ITEM_CODEX, key)
{
}

ItemCodexCommand::~ItemCodexCommand()
{
}

// Switch between sprites and ASCII (when in SDL)
SwitchGraphicsModeCommand::SwitchGraphicsModeCommand(int key)
: Command(CommandKeys::SWITCH_GRAPHICS_MODE, key)
{
}

SwitchGraphicsModeCommand::~SwitchGraphicsModeCommand()
{
}

// Switch between colour palettes (when in SDL)
SwitchColourPalettesCommand::SwitchColourPalettesCommand(int key)
: Command(CommandKeys::SWITCH_COLOUR_PALETTES, key)
{
}

SwitchColourPalettesCommand::~SwitchColourPalettesCommand()
{
}

// Switch between fullscreen and windowed (when in SDL)
ToggleWindowModeCommand::ToggleWindowModeCommand(int key)
: Command(CommandKeys::TOGGLE_WINDOW_MODE, key)
{
}

ToggleWindowModeCommand::~ToggleWindowModeCommand()
{
}
// Give orders to followers
OrderCommand::OrderCommand(int key)
: Command(CommandKeys::ORDER, key)
{
}

OrderCommand::~OrderCommand()
{
}

// NPC-only commands

// Breed (create a new creature of the same ID on an adjacent tile)
BreedCommand::BreedCommand(int key)
  : Command(CommandKeys::BREED, key)
{
}

BreedCommand::~BreedCommand()
{
}
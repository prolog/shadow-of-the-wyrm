#pragma once
#include <memory>
#include <string>
#include "Command.hpp"
#include "Directions.hpp"
#include "EquipmentTypes.hpp"
#include "Item.hpp"

class QuitCommand : public Command
{
  public:
    QuitCommand(int key);
    ~QuitCommand();
};

class VersionCommand : public Command
{
  public:
    VersionCommand(int key);
    ~VersionCommand();
};

class GameDateTimeWeatherCommand : public Command
{
  public:
    GameDateTimeWeatherCommand(int key);
    ~GameDateTimeWeatherCommand();
};

class DirectionalCommand : public Command
{
  public:
    DirectionalCommand(const Direction d, int key);
    virtual ~DirectionalCommand() = 0;
    virtual bool requires_confirmation() const override;

    Direction get_direction() const;

  protected:
    Direction direction;
};

using DirectionalCommandPtr = std::unique_ptr<DirectionalCommand>;

class MovementCommand : public DirectionalCommand
{
  public:
    MovementCommand(const Direction direction, int key);
    virtual ~MovementCommand();

    virtual bool get_allow_clear_message_buffer() const override;
};

class MoveUpLevelCommand : public Command
{
  public:
    MoveUpLevelCommand(int key);
    ~MoveUpLevelCommand();
};

class MoveDownLevelCommand : public Command
{
  public:
    MoveDownLevelCommand(int key);
    ~MoveDownLevelCommand();
};

class AutomaticMovementCommand : public Command
{
  public:
    AutomaticMovementCommand(int key);
    ~AutomaticMovementCommand();

    virtual bool get_allow_clear_message_buffer() const override;
};

class SearchCommand : public MovementCommand
{
  public:
    SearchCommand(int key);
    ~SearchCommand();
};

class PrayCommand : public Command
{
  public:
    PrayCommand(int key);
    ~PrayCommand();
};

class AttackCommand : public DirectionalCommand
{
  public:
    AttackCommand(const Direction d, int key);
    ~AttackCommand();
};

class PickUpCommand : public Command
{
  public:
    PickUpCommand(int key);
    PickUpCommand(const std::string& new_item_id); // NPC version
    ~PickUpCommand();

    std::string get_item_id() const;

  protected:
    std::string item_id;
};

class PickUpAllCommand : public Command
{
  public:
    PickUpAllCommand(int key);
    ~PickUpAllCommand();
};

class DropCommand : public Command
{
  public:
    DropCommand(int key);
    DropCommand(const std::string& new_drop_id);
    ~DropCommand();

    std::string get_drop_id() const;

  protected:
    std::string drop_id;
};

class CharDetailsCommand : public Command
{
  public:
    CharDetailsCommand(int key);
    ~CharDetailsCommand();
};

class CharDumpCommand : public Command
{
  public:
    CharDumpCommand(int key);
    ~CharDumpCommand();
};

class InventoryCommand : public Command
{
  public:
    InventoryCommand(int key);
    InventoryCommand(const EquipmentWornLocation ewl, ItemPtr item);
    ~InventoryCommand();

    EquipmentWornLocation get_equipment_worn_location() const;
    ItemPtr get_item();

protected:
    EquipmentWornLocation ewl;
    ItemPtr i;
};

class MeleeWeaponInfoCommand : public Command
{
  public:
    MeleeWeaponInfoCommand(int key);
    ~MeleeWeaponInfoCommand();
};

class RangedWeaponInfoCommand : public Command
{
  public:
    RangedWeaponInfoCommand(int key);
    ~RangedWeaponInfoCommand();
};

class SelectTileCommand : public Command
{
  public:
    SelectTileCommand(int key);
    ~SelectTileCommand();
};

class FireMissileCommand : public Command
{
  public:
    FireMissileCommand(int key);
    ~FireMissileCommand();
};

class QuaffCommand : public Command
{
  public:
    QuaffCommand(int key);
    ~QuaffCommand();
};

class ReadCommand : public Command
{
  public:
    ReadCommand(const std::string& read_item_id);
    ReadCommand(int key);
    ~ReadCommand();

    std::string get_item_id() const;
  
  protected:
    std::string readable_id;
};

class CheckCurrencyCommand : public Command
{
  public:
    CheckCurrencyCommand(int key);
    ~CheckCurrencyCommand();
};

class SaveGameCommand : public Command
{
  public:
    SaveGameCommand(int key);
    ~SaveGameCommand();
};

class EatCommand : public Command
{
  public:
    EatCommand(int key);
    ~EatCommand();
};

class ChatCommand : public Command
{
  public:
    ChatCommand(int key);
    ~ChatCommand();
};

class ApplyFeatureCommand : public Command
{
  public:
    ApplyFeatureCommand(int key);
    ~ApplyFeatureCommand();
};

class QuestListCommand : public Command
{
  public:
    QuestListCommand(int key);
    ~QuestListCommand();
};

class ReloadScriptsCommand : public Command
{
  public:
    ReloadScriptsCommand(int key);
    ~ReloadScriptsCommand();
};

class RunScriptCommand : public Command
{
  public:
    RunScriptCommand(int key);
    ~RunScriptCommand();
};

class CastSpellCommand : public Command
{
  public:
    CastSpellCommand(int key);
    ~CastSpellCommand();
};

class BestiaryCommand : public Command
{
  public:
    BestiaryCommand(int key);
    ~BestiaryCommand();
};

class EvokeCommand : public Command
{
  public:
    EvokeCommand(int key);
    EvokeCommand(const std::string& new_item_id, const Direction new_d);
    ~EvokeCommand();

    std::string get_item_id() const;
    Direction get_direction() const;

  protected:
    std::string item_id;
    Direction d;
};

class ShowResistancesCommand : public Command
{
  public:
    ShowResistancesCommand(int key);
    ~ShowResistancesCommand();
};

class ShowConductsCommand : public Command
{
  public:
    ShowConductsCommand(int key);
    ~ShowConductsCommand();
};

class ShowSkillsCommand : public Command
{
  public:
    ShowSkillsCommand(int key);
    ~ShowSkillsCommand();
};

class LatestMessagesCommand : public Command
{
  public:
    LatestMessagesCommand(int key);
    ~LatestMessagesCommand();
};

class KickCommand : public DirectionalCommand
{
  public:
    KickCommand(int key);
    KickCommand(const Direction kick_dir, const int key);

    ~KickCommand();
};

class OfferCommand : public Command
{
  public:
    OfferCommand(int key);
    ~OfferCommand();
};

class SkinCommand : public Command
{
  public:
    SkinCommand(int key);
    ~SkinCommand();
};

class PietyCommand : public Command
{
  public:
    PietyCommand(int key);
    ~PietyCommand();
};

class ExperienceCommand : public Command
{
  public:
    ExperienceCommand(int key);
    ~ExperienceCommand();
};

class CustomScriptCommand : public Command
{
  public:
    CustomScriptCommand();
    ~CustomScriptCommand();
};

class RestCommand : public DirectionalCommand
{
  public:
    RestCommand(int key);
    ~RestCommand();
};

class ViewItemsCommand : public Command
{
  public:
    ViewItemsCommand(int key);
    ~ViewItemsCommand();
};

class HelpCommand : public Command
{
  public:
    HelpCommand(int key);
    ~HelpCommand();
};

class InscribeCommand : public Command
{
  public:
    InscribeCommand(int key);
    ~InscribeCommand();
};

class AutomaticActionsCommand : public Command
{
  public:
    AutomaticActionsCommand(int key);
    ~AutomaticActionsCommand();
};

class SoundActionsCommand : public Command
{
  public:
    SoundActionsCommand(int key);
    ~SoundActionsCommand();
};

class ItemCodexCommand : public Command
{
  public:
    ItemCodexCommand(int key);
    ~ItemCodexCommand();
};

class SwitchGraphicsModeCommand : public Command
{
  public:
    SwitchGraphicsModeCommand(int key);
    ~SwitchGraphicsModeCommand();
};

class SwitchColourPalettesCommand : public Command
{
  public:
    SwitchColourPalettesCommand(int key);
    ~SwitchColourPalettesCommand();
};

class ToggleWindowModeCommand : public Command
{
  public:
    ToggleWindowModeCommand(int key);
    ~ToggleWindowModeCommand();
};

class OrderCommand : public Command
{
  public:
    OrderCommand(int key);
    ~OrderCommand();
};

// NPC-only commands:

class BreedCommand : public Command
{
  public:
    BreedCommand(int key);
    ~BreedCommand();
};
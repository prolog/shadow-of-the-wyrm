#pragma once
#include <memory>
#include "Command.hpp"
#include "Directions.hpp"

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

class GameDateTimeCommand : public Command
{
  public:
    GameDateTimeCommand(int key);
    ~GameDateTimeCommand();
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

using DirectionalCommandPtr = std::shared_ptr<DirectionalCommand>;

class MovementCommand : public DirectionalCommand
{
  public:
    MovementCommand(const Direction direction, int key);
    ~MovementCommand();

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
    ~PickUpCommand();
};

class DropCommand : public Command
{
  public:
    DropCommand(int key);
    ~DropCommand();
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
    ~InventoryCommand();
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
    ReadCommand(int key);
    ~ReadCommand();
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
    ~EvokeCommand();
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

class LatestMessagesCommand : public Command
{
  public:
    LatestMessagesCommand(int key);
    ~LatestMessagesCommand();
};

class KickCommand : public Command
{
  public:
    KickCommand(int key);
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
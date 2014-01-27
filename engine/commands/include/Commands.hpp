#pragma once
#include <memory>
#include "Command.hpp"
#include "Directions.hpp"

class QuitCommand : public Command
{
  public:
    QuitCommand();
    ~QuitCommand();
};

class VersionCommand : public Command
{
  public:
    VersionCommand();
    ~VersionCommand();
};

class GameDateTimeCommand : public Command
{
  public:
    GameDateTimeCommand();
    ~GameDateTimeCommand();
};

class DirectionalCommand : public Command
{
  public:
    DirectionalCommand(const Direction d);
    virtual ~DirectionalCommand() = 0;
    virtual bool requires_confirmation() const override;

    Direction get_direction() const;

  protected:
    Direction direction;
};

typedef std::shared_ptr<DirectionalCommand> DirectionalCommandPtr;

class MovementCommand : public DirectionalCommand
{
  public:
    MovementCommand(const Direction direction);
    ~MovementCommand();
};

class MoveUpLevelCommand : public Command
{
  public:
    MoveUpLevelCommand();
    ~MoveUpLevelCommand();
};

class MoveDownLevelCommand : public Command
{
  public:
    MoveDownLevelCommand();
    ~MoveDownLevelCommand();
};

class AutomaticMovementCommand : public Command
{
  public:
    AutomaticMovementCommand();
    ~AutomaticMovementCommand();
};

class SearchCommand : public MovementCommand
{
  public:
    SearchCommand();
    ~SearchCommand();
};

class PrayCommand : public Command
{
  public:
    PrayCommand();
    ~PrayCommand();
};

class AttackCommand : public DirectionalCommand
{
  public:
    AttackCommand(const Direction d);
    ~AttackCommand();
};

class PickUpCommand : public Command
{
  public:
    PickUpCommand();
    ~PickUpCommand();
};

class DropCommand : public Command
{
  public:
    DropCommand();
    ~DropCommand();
};

class CharDumpCommand : public Command
{
  public:
    CharDumpCommand();
    ~CharDumpCommand();
};

class InventoryCommand : public Command
{
  public:
    InventoryCommand();
    ~InventoryCommand();
};

class MeleeWeaponInfoCommand : public Command
{
  public:
    MeleeWeaponInfoCommand();
    ~MeleeWeaponInfoCommand();
};

class RangedWeaponInfoCommand : public Command
{
  public:
    RangedWeaponInfoCommand();
    ~RangedWeaponInfoCommand();
};

class SelectTileCommand : public Command
{
  public:
    SelectTileCommand();
    ~SelectTileCommand();
};

class FireMissileCommand : public Command
{
  public:
    FireMissileCommand();
    ~FireMissileCommand();
};

class QuaffCommand : public Command
{
  public:
    QuaffCommand();
    ~QuaffCommand();
};

class ReadCommand : public Command
{
  public:
    ReadCommand();
    ~ReadCommand();
};

class CheckCurrencyCommand : public Command
{
  public:
    CheckCurrencyCommand();
    ~CheckCurrencyCommand();
};

class SaveGameCommand : public Command
{
  public:
    SaveGameCommand();
    ~SaveGameCommand();
};

class EatCommand : public Command
{
  public:
    EatCommand();
    ~EatCommand();
};

class ChatCommand : public Command
{
  public:
    ChatCommand();
    ~ChatCommand();
};

class ApplyFeatureCommand : public Command
{
  public:
    ApplyFeatureCommand();
    ~ApplyFeatureCommand();
};

class QuestListCommand : public Command
{
  public:
    QuestListCommand();
    ~QuestListCommand();
};

class ReloadScriptsCommand : public Command
{
  public:
    ReloadScriptsCommand();
    ~ReloadScriptsCommand();
};

class RunScriptCommand : public Command
{
  public:
    RunScriptCommand();
    ~RunScriptCommand();
};

class CastSpellCommand : public Command
{
  public:
    CastSpellCommand();
    ~CastSpellCommand();
};

class BestiaryCommand : public Command
{
  public:
    BestiaryCommand();
    ~BestiaryCommand();
};

class EvokeCommand : public Command
{
  public:
    EvokeCommand();
    ~EvokeCommand();
};

class ShowResistancesCommand : public Command
{
  public:
    ShowResistancesCommand();
    ~ShowResistancesCommand();
};

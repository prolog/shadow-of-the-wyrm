#pragma once
#include <memory>
#include "Command.hpp"
#include "Directions.hpp"
#include "TileSelectionCommandKeys.hpp"

class CursorDirectionalCommand : public Command
{
  public:
    CursorDirectionalCommand(const Direction d);
    ~CursorDirectionalCommand();

    Direction get_direction() const;

  protected:
    Direction direction;
};

class CancelTileSelectionCommand : public Command
{
  public:
    CancelTileSelectionCommand();
    ~CancelTileSelectionCommand();
};

class TargetTileCommand : public Command
{
  public:
    TargetTileCommand();
    ~TargetTileCommand();
};

typedef std::shared_ptr<CursorDirectionalCommand> CursorDirectionalCommandPtr;


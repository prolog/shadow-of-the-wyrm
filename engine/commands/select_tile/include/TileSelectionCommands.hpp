#pragma once
#include <boost/shared_ptr.hpp>
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

typedef boost::shared_ptr<CursorDirectionalCommand> CursorDirectionalCommandPtr;


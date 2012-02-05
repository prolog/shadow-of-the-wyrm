#pragma once
#include <boost/shared_ptr.hpp>
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

class DirectionalCommand : public Command
{
  public:
    DirectionalCommand(const Direction d);
    virtual ~DirectionalCommand() = 0;
    virtual bool requires_confirmation() const;

    Direction get_direction() const;

  protected:
    Direction direction;
};

typedef boost::shared_ptr<DirectionalCommand> DirectionalCommandPtr;

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

class SearchCommand : public Command
{
  public:
    SearchCommand();
    ~SearchCommand();
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

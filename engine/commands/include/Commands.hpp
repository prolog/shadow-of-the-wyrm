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

class SearchCommand : public Command
{
  public:
    SearchCommand();
    ~SearchCommand();
};

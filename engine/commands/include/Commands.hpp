#pragma once
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

class MovementCommand : public Command
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

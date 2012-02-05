#include "Command.hpp"

using namespace std;

Command::Command(const string& name)
: command_name(name)
{
}

Command::Command(const string& name, const string& confirm)
: command_name(name), command_confirmation(confirm)
{
}

Command::~Command()
{
}

string Command::get_name() const
{
  return command_name;
}

bool Command::requires_confirmation() const
{
  return (!command_confirmation.empty());
}

string Command::get_confirmation_sid() const
{
  return command_confirmation;
}

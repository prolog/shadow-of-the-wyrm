#include "Command.hpp"

using namespace std;

Command::Command(const string& name, const int ckey)
: command_name(name), key_pressed(ckey)
{
}

Command::Command(const string& name, const int ckey, const string& confirm)
: command_name(name), key_pressed(ckey), command_confirmation(confirm)
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

int Command::get_key() const
{
  return key_pressed;
}
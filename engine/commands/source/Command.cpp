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

void Command::set_custom_value(const string& key, const string& value)
{
  custom_values[key] = value;
}

string Command::get_custom_value(const string& key) const
{
  string val;

  auto c_it = custom_values.find(key);

  if (c_it != custom_values.end())
  {
    val = c_it->second;
  }

  return val;
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

bool Command::get_allow_clear_message_buffer() const
{
  return true;
}
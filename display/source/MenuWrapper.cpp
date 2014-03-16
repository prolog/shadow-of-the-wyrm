#include "MenuWrapper.hpp"
#include "MenuKeyboardCommandMap.hpp"
#include "Conversion.hpp"
#include "Log.hpp"

using namespace std;

MenuWrapper::MenuWrapper()
{
  MenuKeyboardCommandMap mkcm;

  // Automatically include the paging keyboard commands in the set -
  // these should be recognizable for all menus.
  for (auto& map_pair : mkcm.get_internal_map())
  {
    string cmd = map_pair.first;

    if (!cmd.empty())
    {
      options.insert(String::to_int(cmd));
    }
  }
}

int MenuWrapper::get_num_items() const
{
  return options.size();
}

bool MenuWrapper::has_options() const
{
  return (!options.empty());
}

void MenuWrapper::add_options(OptionsComponentPtr options)
{
  if (options != nullptr)
  {
    auto op = options->get_options();

    for (auto& o : op)
    {
      char option = o.get_id() + 'a';
      add_option(option);
    }
  }
}

void MenuWrapper::add_option(const char option)
{
  options.insert(option);
}

bool MenuWrapper::is_option_in_set(const char option) const
{
  return (options.find(option) != options.end());
}


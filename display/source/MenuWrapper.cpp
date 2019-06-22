#include "MenuWrapper.hpp"
#include "ScreenKeyboardCommandMap.hpp"
#include "Conversion.hpp"
#include "Log.hpp"

using namespace std;

MenuWrapper::MenuWrapper()
{
  ScreenKeyboardCommandMap skcm;
  auto internal_map = skcm.get_internal_map();

  // Automatically include the paging keyboard commands in the set -
  // these should be recognizable for all menus.
  for (auto& map_pair : internal_map)
  {
    string cmd = map_pair.first;

    if (!cmd.empty())
    {
      options.insert(cmd.at(0));
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


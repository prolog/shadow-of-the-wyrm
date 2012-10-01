#include "NCursesMenuWrapper.hpp"
#include "Conversion.hpp"
#include "Log.hpp"

NCursesMenuWrapper::NCursesMenuWrapper()
: num_items(0)
{
}

NCursesMenuWrapper::NCursesMenuWrapper(const int new_num_items) 
: num_items(new_num_items)
{
}

void NCursesMenuWrapper::set_num_items(const int new_num_items)
{
  num_items = new_num_items;
}

int NCursesMenuWrapper::get_num_items() const
{
  return num_items;
}

bool NCursesMenuWrapper::has_options() const
{
  return (!options.empty());
}

void NCursesMenuWrapper::clear_options()
{
  options.clear();
}

void NCursesMenuWrapper::add_option(const char option)
{
  options.insert(option);
}

bool NCursesMenuWrapper::is_option_in_set(const char option) const
{
  return (options.find(option) != options.end());
}


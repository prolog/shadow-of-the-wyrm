#include "CursesMenuWrapper.hpp"
#include "Conversion.hpp"
#include "Log.hpp"

CursesMenuWrapper::CursesMenuWrapper()
: num_items(0)
{
}

CursesMenuWrapper::CursesMenuWrapper(const int new_num_items) 
: num_items(new_num_items)
{
}

void CursesMenuWrapper::set_num_items(const int new_num_items)
{
  num_items = new_num_items;
}

int CursesMenuWrapper::get_num_items() const
{
  return num_items;
}

bool CursesMenuWrapper::has_options() const
{
  return (!options.empty());
}

void CursesMenuWrapper::clear_options()
{
  options.clear();
}

void CursesMenuWrapper::add_option(const char option)
{
  options.insert(option);
}

bool CursesMenuWrapper::is_option_in_set(const char option) const
{
  return (options.find(option) != options.end());
}


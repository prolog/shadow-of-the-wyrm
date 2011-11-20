#include "OptionsComponent.hpp"

using namespace std;

// Option - an individual menu option
Option::Option()
: id(-1)
{
}

Option::Option(const int new_id, const string& new_description)
: id(new_id), description(new_description)
{
}

void Option::set_id(const int new_id)
{
  id = new_id;
}

int Option::get_id() const
{
  return id;
}

void Option::set_description(const string& new_description)
{
  description = new_description;
}

string Option::get_description() const
{
  return description;
}

// Options - a container for Option menu objects.

OptionsComponent::OptionsComponent()
{
  clear_options();
}

void OptionsComponent::clear_options()
{
  options.clear();
}

void OptionsComponent::add_option(const Option& additional_option)
{
  options.push_back(additional_option);
}

vector<Option> OptionsComponent::get_options() const
{
  return options;
}

void OptionsComponent::clear_option_descriptions()
{
  option_descriptions.clear();
}

void OptionsComponent::add_option_description(const string& desc)
{
  option_descriptions.push_back(desc);
}

vector<string> OptionsComponent::get_option_descriptions() const
{
  return option_descriptions;
}

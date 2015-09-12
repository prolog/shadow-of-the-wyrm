#include "OptionsComponent.hpp"

using namespace std;

// Option - an individual menu option
Option::Option()
: id(-1), external_id(""), colour(Colour::COLOUR_WHITE)
{
  description = std::make_shared<TextComponent>(string(""));
}

Option::Option(const int new_id, const string& new_external_id, const string& new_description)
: id(new_id), external_id(new_external_id), colour(Colour::COLOUR_WHITE)
{
  description = std::make_shared<TextComponent>(string(""));
}

void Option::set_id(const int new_id)
{
  id = new_id;
}

int Option::get_id() const
{
  return id;
}

char Option::get_id_char() const
{
  return (id + 'a');
}

void Option::set_external_id(const string& new_external_id)
{
  external_id = new_external_id;
}

string Option::get_external_id() const
{
  return external_id;
}

void Option::set_description(const string& new_description)
{
  description->add_text(new_description);
}

TextComponentPtr Option::get_description() const
{
  return TextComponentPtr(description);
}

void Option::set_colour(const Colour new_colour)
{
  colour = new_colour;
}

Colour Option::get_colour() const
{
  return colour;
}

// Options - a container for Option menu objects.

OptionsComponent::OptionsComponent()
: show_option_descriptions(true)
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

vector<Option>& OptionsComponent::get_options_ref()
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

void OptionsComponent::set_show_option_descriptions(const bool new_show_option_descriptions)
{
  show_option_descriptions = new_show_option_descriptions;
}

bool OptionsComponent::get_show_option_descriptions() const
{
  return show_option_descriptions;
}
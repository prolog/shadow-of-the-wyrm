#include "OptionsComponent.hpp"

using namespace std;

// Option - an individual menu option
Option::Option()
: id(-1), external_id(""), colour(Colour::COLOUR_WHITE), enabled(true), uppercase(false)
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

void Option::set_enabled(const bool new_enabled)
{
  enabled = new_enabled;
}

bool Option::get_enabled() const
{
  return enabled;
}

int Option::get_id_for_random() const
{
  return '*' - 'a';
}

bool Option::is_random_option(const int opt) const
{
  return (opt == '*');
}

char Option::get_id_char() const
{
  char id_char = static_cast<char>(id) + 'a';

  if (uppercase)
  {
    id_char = static_cast<char>(toupper(id_char));
  }

  return id_char;
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
  if (!enabled)
  {
    description->set_colour(get_colour());
  }

  return description;
}

void Option::set_colour(const Colour new_colour)
{
  colour = new_colour;
}

Colour Option::get_colour() const
{
  if (enabled)
  {
    return colour;
  }
  else
  {
    return Colour::COLOUR_BOLD_BLACK;
  }
}

void Option::set_uppercase(const bool new_uppercase)
{
  uppercase = new_uppercase;
}

bool Option::get_uppercase() const
{
  return uppercase;
}

void Option::set_property(const string& prop, const string& val)
{
  properties[prop] = val;
}

void Option::set_properties(const map<string, string>& new_properties)
{
  properties = new_properties;
}

bool Option::has_property(const string& prop) const
{
  const auto p_it = properties.find(prop);

  return (p_it != properties.end());
}

string Option::get_property(const string& prop) const
{
  string val;
  auto p_it = properties.find(prop);

  if (p_it != properties.end())
  {
    val = p_it->second;
  }

  return val;
}

map<string, string> Option::get_properties() const
{
  return properties;
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

#ifdef UNIT_TESTS
#include "unit_tests/OptionsComponent_test.cpp"
#endif
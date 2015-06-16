#include "ScreenComponent.hpp"

ScreenComponent::ScreenComponent()
{
}

ScreenComponent::ScreenComponent(const std::string& new_text)
{
  text.push_back(make_pair(new_text, Colour::COLOUR_WHITE));
}

ScreenComponent::ScreenComponent(const std::string& new_text, const Colour new_colour)
{
  text.push_back(make_pair(new_text, new_colour));
}

void ScreenComponent::set_text(const std::vector<std::pair<std::string, Colour>>& new_text)
{
  text = new_text;
}

void ScreenComponent::add_text(const std::string& new_text)
{
  text.push_back(make_pair(new_text, Colour::COLOUR_WHITE));
}

void ScreenComponent::add_text(const std::string& new_text, const Colour new_colour)
{
  text.push_back(make_pair(new_text, new_colour));
}

std::vector<std::pair<std::string, Colour>> ScreenComponent::get_text() const
{
  return text;
}

void ScreenComponent::set_spacing_after(const ComponentAlignment& new_component_alignment)
{
  ca = new_component_alignment;
}

ComponentAlignment ScreenComponent::get_spacing_after() const
{
  return ca;
}


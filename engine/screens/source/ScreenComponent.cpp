#include "ScreenComponent.hpp"

ScreenComponent::ScreenComponent()
{
}

ScreenComponent::ScreenComponent(const std::string& new_text)
{
  text.push_back(make_pair(new_text, COLOUR_WHITE));
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
  text.push_back(make_pair(new_text, COLOUR_WHITE));
}

void ScreenComponent::add_text(const std::string& new_text, const Colour new_colour)
{
  text.push_back(make_pair(new_text, new_colour));
}

std::vector<std::pair<std::string, Colour>> ScreenComponent::get_text() const
{
  return text;
}


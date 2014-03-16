#include "MenuComponent.hpp"

MenuComponent::MenuComponent()
{
}

MenuComponent::MenuComponent(const std::string& new_text)
{
  text.push_back(make_pair(new_text, COLOUR_WHITE));
}

MenuComponent::MenuComponent(const std::string& new_text, const Colour new_colour)
{
  text.push_back(make_pair(new_text, new_colour));
}

void MenuComponent::set_text(const std::vector<std::pair<std::string, Colour>>& new_text)
{
  text = new_text;
}

void MenuComponent::add_text(const std::string& new_text)
{
  text.push_back(make_pair(new_text, COLOUR_WHITE));
}

void MenuComponent::add_text(const std::string& new_text, const Colour new_colour)
{
  text.push_back(make_pair(new_text, new_colour));
}

std::vector<std::pair<std::string, Colour>> MenuComponent::get_text() const
{
  return text;
}


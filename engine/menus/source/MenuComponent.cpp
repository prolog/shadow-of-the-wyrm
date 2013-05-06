#include "MenuComponent.hpp"

MenuComponent::MenuComponent() : colour(COLOUR_WHITE)
{
}

MenuComponent::MenuComponent(const std::string& new_text)
: text(new_text), colour(COLOUR_WHITE)
{
}

MenuComponent::MenuComponent(const std::string& new_text, const Colour new_colour)
: text(new_text), colour(new_colour)
{
}

void MenuComponent::set_text(const std::string& new_text)
{
  text = new_text;
}

std::string MenuComponent::get_text() const
{
  return text;
}

void MenuComponent::set_colour(const Colour new_colour)
{
  colour = new_colour;
}

Colour MenuComponent::get_colour() const
{
  return colour;
}

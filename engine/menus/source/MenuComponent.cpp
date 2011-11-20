#include "MenuComponent.hpp"


MenuComponent::MenuComponent(const std::string& new_text)
: text(new_text)
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

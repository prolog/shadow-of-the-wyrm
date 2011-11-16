#include "TextComponent.hpp"

TextComponent::TextComponent(const std::string& new_text)
: text(new_text)
{
}

void TextComponent::set_text(const std::string& new_text)
{
  text = new_text;
}

std::string TextComponent::get_text() const
{
  return text;
}

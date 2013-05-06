#include "TextComponent.hpp"

TextComponent::TextComponent(const std::string& str) : MenuComponent(str)
{
}

TextComponent::TextComponent(const std::string& str, const Colour colour) : MenuComponent(str, colour)
{
}
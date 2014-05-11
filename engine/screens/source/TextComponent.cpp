#include "TextComponent.hpp"

TextComponent::TextComponent(const std::string& str) : ScreenComponent(str)
{
}

TextComponent::TextComponent(const std::string& str, const Colour colour) : ScreenComponent(str, colour)
{
}
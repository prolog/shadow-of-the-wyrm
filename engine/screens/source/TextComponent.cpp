#include "TextComponent.hpp"

TextComponent::TextComponent(const std::string& str, const std::vector<Symbol>& symbols) : ScreenComponent(str, symbols)
{
}

TextComponent::TextComponent(const std::string& str, const Colour colour, const std::vector<Symbol>& symbols) : ScreenComponent(str, colour, symbols)
{
}

#pragma once
#include <string>
#include <memory>
#include "MenuComponent.hpp"

class TextComponent : public MenuComponent
{
  public:
    TextComponent(const std::string& str);
    TextComponent(const std::string& str, const Colour c);
};

typedef std::shared_ptr<TextComponent> TextComponentPtr;

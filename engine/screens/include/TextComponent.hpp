#pragma once
#include <string>
#include <memory>
#include "ScreenComponent.hpp"

class TextComponent : public ScreenComponent
{
  public:
    TextComponent(const std::string& str, const std::vector<Symbol>& symbols = {});
    TextComponent(const std::string& str, const Colour c, const std::vector<Symbol>& symbols = {});
};

using TextComponentPtr = std::shared_ptr<TextComponent>;

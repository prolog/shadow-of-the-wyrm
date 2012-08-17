#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include "MenuComponent.hpp"

class TextComponent : public MenuComponent
{
  public:
    TextComponent(const std::string& str);

  protected:
};

typedef boost::shared_ptr<TextComponent> TextComponentPtr;

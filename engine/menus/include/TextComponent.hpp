#pragma once
#include <string>
#include "MenuComponent.hpp"

class TextComponent : public MenuComponent
{
  public:
    TextComponent(const std::string& new_text);

    void set_text(const std::string& new_text);
    std::string get_text() const;

  protected:
    std::string text;
};

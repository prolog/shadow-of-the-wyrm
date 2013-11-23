#pragma once
#include <memory>
#include <string>
#include "Colours.hpp"

class MenuComponent
{
  public:
    MenuComponent();
    MenuComponent(const std::string& new_text);
    MenuComponent(const std::string& new_text, const Colour new_colour);

    virtual void set_text(const std::string& new_text);
    virtual std::string get_text() const;

    virtual void set_colour(const Colour new_colour);
    virtual Colour get_colour() const;

  protected:
    std::string text;
    Colour colour;
};

typedef std::shared_ptr<MenuComponent> MenuComponentPtr;

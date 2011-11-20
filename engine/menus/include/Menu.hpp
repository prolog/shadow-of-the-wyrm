#pragma once
#include <string>
#include <vector>
#include "TextComponent.hpp"
#include "Prompt.hpp"
#include "Display.hpp"

class Menu
{
  public:
    Menu(DisplayPtr display);
    virtual ~Menu();

    virtual std::string display();
    virtual std::string prompt();

    PromptPtr get_prompt() const;

    std::vector<MenuComponent*> get_components() const;

  protected:
    virtual void initialize();

    std::vector<MenuComponent*> components;
    PromptPtr user_prompt;

    DisplayPtr game_display;
};

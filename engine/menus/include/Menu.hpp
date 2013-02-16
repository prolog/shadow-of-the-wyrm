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

    uint get_line_increment() const;

    PromptPtr get_prompt() const;

    std::vector<MenuComponentPtr> get_components() const;

  protected:
    virtual void initialize();

    std::vector<MenuComponentPtr> components;
    PromptPtr user_prompt;

    DisplayPtr game_display;
    uint line_increment;
};

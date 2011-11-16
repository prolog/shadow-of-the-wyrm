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
    ~Menu();

    virtual std::string display();
    virtual std::string prompt();

    PromptPtr get_prompt() const;

    std::vector<TextComponent> get_text() const;

  protected:
    virtual void initialize();

    std::vector<TextComponent> text;
    PromptPtr user_prompt;

    DisplayPtr game_display;
};

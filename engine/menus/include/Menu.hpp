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

    // Set/get the title text SID, which is interpreted differently than the
    // other components by the display.
    void set_title_text_sid(const std::string& new_title_text_sid);
    std::string get_title_text_sid() const;

    virtual std::string display();
    virtual std::string prompt();

    uint get_line_increment() const;

    void set_prompt(PromptPtr new_prompt);
    PromptPtr get_prompt() const;

    std::vector<std::vector<MenuComponentPtr>> get_components() const;
    std::vector<MenuComponentPtr> get_current_page() const;

  protected:
    virtual void initialize();

    void add_page(const std::vector<MenuComponentPtr>& new_page);

    // The menu's title.  May be empty (and will be for things like the race/
    // class selection screens, the welcome screen, etc).  This is used for in-game
    // menus that need a title across the top.
    std::string title_text_sid;

    PromptPtr user_prompt;

    DisplayPtr game_display;
    uint line_increment;
    uint cur_page_idx;

  private:
    std::vector<std::vector<MenuComponentPtr>> components;
};

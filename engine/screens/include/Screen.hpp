#pragma once
#include <string>
#include <vector>
#include "TextComponent.hpp"
#include "OptionsComponent.hpp"
#include "Prompt.hpp"
#include "Display.hpp"

class Screen
{
  public:
    Screen(DisplayPtr display);
    virtual ~Screen();

    // Set/get the title text SID, which is interpreted differently than the
    // other components by the display.
    void set_title_text_sid(const std::string& new_title_text_sid);
    std::string get_title_text_sid() const;

    virtual std::string display();
    virtual std::string prompt();

    uint get_line_increment() const;
    uint get_cur_page_idx() const;

    void set_current_page_number(const uint new_page);
    uint get_current_page_number() const;
    uint get_num_pages() const;

    OptionPtr get_option(const int option_id);

    void set_prompt(PromptPtr new_prompt);
    PromptPtr get_prompt() const;

    std::vector<std::vector<ScreenComponentPtr>> get_components() const;
    std::vector<ScreenComponentPtr> get_current_page() const;

    static const int LINES_DISPLAYABLE_AREA;

  protected:
    virtual void initialize();

    // Handle adding a component to the current screen - add it, and then if the
    // current item count has reached the maximum, reset the count, add the
    // current screen to the list of pages, etc.
    void add_component(std::vector<ScreenComponentPtr>& current_menu, ScreenComponentPtr component, int& cnt);

    // Add the current page to the list of pages for this screen.
    void add_page(const std::vector<ScreenComponentPtr>& new_page);

    // The screen's title.  May be empty (and will be for things like the race/
    // class selection screens, the welcome screen, etc).  This is used for in-game
    // screens that need a title across the top.
    std::string title_text_sid;

    PromptPtr user_prompt;

    int num_screens_created;

    DisplayPtr game_display;
    uint line_increment;
    uint cur_page_idx;

  private:
    std::vector<std::vector<ScreenComponentPtr>> components;
};

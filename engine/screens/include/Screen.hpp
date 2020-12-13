#pragma once
#include <deque>
#include <string>
#include <vector>
#include "TextComponent.hpp"
#include "OptionsComponent.hpp"
#include "Prompt.hpp"
#include "Display.hpp"

using TextDisplayPair = std::pair<Colour, std::string>;

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
    std::vector<OptionPtr> get_options();

    Prompt* get_prompt() const;

    static int get_lines_displayable_area(DisplayPtr display);

    std::vector<std::vector<ScreenComponentPtr>> get_components() const;
    std::vector<ScreenComponentPtr> get_current_page() const;

  protected:
    virtual void initialize();

    // Handle adding a component to the current screen - add it, and then if the
    // current item count has reached the maximum, reset the count, add the
    // current screen to the list of pages, etc.  Returns true if a new page was
    // added.
    bool add_options_component(std::vector<ScreenComponentPtr>& current_menu, OptionsComponentPtr options, int& cnt, int& current_option_id);
    bool add_component(std::vector<ScreenComponentPtr>& current_menu, ScreenComponentPtr component, int& cnt);
    bool add_component(std::vector<ScreenComponentPtr>& current_menu, ScreenComponentPtr component, int& cnt, int& current_option_id);
    bool add_text(std::vector<ScreenComponentPtr>& text_screen, const std::vector<TextDisplayPair>& tdp, std::deque<Symbol>& symbols, const bool preserve_formatting, int& cnt);

    bool can_add_component(int component_count) const;

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
    int lines_displayable_area;

  private:
    std::vector<std::vector<ScreenComponentPtr>> components;
};

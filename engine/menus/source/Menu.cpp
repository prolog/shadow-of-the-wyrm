#include "Menu.hpp"

using namespace std;

// Any base initialization for the Menu
Menu::Menu(DisplayPtr new_display)
: line_increment(2), cur_page_idx(0)
{
  game_display = new_display;
  user_prompt = std::make_shared<NullPrompt>();
}

Menu::~Menu()
{
  game_display->clear_menu();
}

// Do whatever work is necessary to initialize the menu
void Menu::initialize()
{
  // Subclasses should always override this method.
}

void Menu::set_title_text_sid(const string& new_title_text_sid)
{
  title_text_sid = new_title_text_sid;
}

std::string Menu::get_title_text_sid() const
{
  return title_text_sid;
}

// Display the contents of the Menu to the user via the DisplayPtr.
string Menu::display()
{
  string menu_selection = game_display->display_menu(*this);
  return menu_selection;
}

// Display a prompt to the user, and get the user's response.
string Menu::prompt()
{
  string empty_str;
  return empty_str;
}

void Menu::add_page(const vector<MenuComponentPtr>& new_page)
{
  components.push_back(new_page);

  if (components.size() > 1)
  {
    cur_page_idx++;
  }
}

void Menu::set_prompt(PromptPtr new_prompt)
{
  user_prompt = new_prompt;
}

PromptPtr Menu::get_prompt() const
{
  return user_prompt;
}

vector<vector<MenuComponentPtr>> Menu::get_components() const
{
  return components;
}

vector<MenuComponentPtr> Menu::get_current_page() const
{
  return components.at(cur_page_idx);
}

// Get the line spacing.
uint Menu::get_line_increment() const
{
  return line_increment;
}

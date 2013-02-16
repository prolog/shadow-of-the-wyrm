#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "Menu.hpp"

using namespace boost;
using namespace std;

// Any base initialization for the Menu
Menu::Menu(DisplayPtr new_display)
: line_increment(2)
{
  game_display = new_display;
  user_prompt = boost::make_shared<NullPrompt>();
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

PromptPtr Menu::get_prompt() const
{
  return user_prompt;
}

vector<MenuComponentPtr> Menu::get_components() const
{
  return components;
}

// Get the line spacing.
uint Menu::get_line_increment() const
{
  return line_increment;
}

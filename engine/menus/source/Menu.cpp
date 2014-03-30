#include "Conversion.hpp"
#include "Menu.hpp"
#include "MenuCommandFactory.hpp"
#include "MenuCommandKeys.hpp"
#include "MenuKeyboardCommandMap.hpp"

using namespace std;

int Menu::LINES_DISPLAYABLE_AREA = 18;

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

// Return the first option with the given option id, or a null OptionPtr
// if none is found.  While this is a shared_ptr, the shared_ptr is just
// used to indicate whether there is an option or not.  It points at a
// copy of the real option, to ensure immutability.
OptionPtr Menu::get_option(const int op_id)
{
  OptionPtr option;

  // Iterate through the current page.
  // Check each option component for the option_id.
  // Return the first match.
  auto cur_page = get_current_page();
  for (auto comp : cur_page)
  {
    auto as_options = dynamic_pointer_cast<OptionsComponent>(comp);
    
    if (as_options != nullptr)
    {
      auto ops = as_options->get_options();

      for (auto op : ops)
      {
        if (op.get_id() == op_id)
        {
          option = make_shared<Option>(op);
          return option;
        }
      }
    }
  }

  return option;
}

// Display the contents of the Menu to the user via the DisplayPtr.
string Menu::display()
{
  bool done = false;
  string menu_selection;

  while (!done)
  {
    menu_selection = game_display->display_menu(*this);
    done = true;

    if (!menu_selection.empty())
    {
      CommandFactoryPtr command_factory = std::make_shared<MenuCommandFactory>();
      KeyboardCommandMapPtr kb_command_map = std::make_shared<MenuKeyboardCommandMap>();
      CommandPtr command = command_factory->create(String::to_int(menu_selection), kb_command_map->get_command_type(menu_selection));

      if (command != nullptr)
      {
        uint pn = get_current_page_number();
        string name = command->get_name();

        if (name == MenuCommandKeys::NEXT_PAGE)
        {
          set_current_page_number(pn + 1);
        }
        else if (name == MenuCommandKeys::PREVIOUS_PAGE)
        {
          set_current_page_number(pn - 1);
        }

        done = false;

        // We're going to create another menu, because we've determined
        // we need to try changing the page.
        //
        // Destroy the current menu.
        game_display->clear_menu();
      }
    }
  }

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

// Get the current page number, internally
uint Menu::get_cur_page_idx() const
{
  return cur_page_idx;
}

// Set the current page number, assuming sane input
void Menu::set_current_page_number(const uint new_page_number)
{
  if (new_page_number >= 1 && new_page_number <= components.size())
  {
    cur_page_idx = new_page_number-1;
  }
}

// Get the current page number, for external use (ie, idx 0 is pg. 1)
uint Menu::get_current_page_number() const
{
  return (cur_page_idx + 1);
}

// Get the total number of pages
uint Menu::get_num_pages() const
{
  return components.size();
}
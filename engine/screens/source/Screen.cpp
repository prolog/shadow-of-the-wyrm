#include "Conversion.hpp"
#include "Screen.hpp"
#include "ScreenCommandFactory.hpp"
#include "ScreenCommandKeys.hpp"
#include "ScreenKeyboardCommandMap.hpp"

using namespace std;

const int Screen::LINES_DISPLAYABLE_AREA = 21;

// Any base initialization for the Screen
Screen::Screen(DisplayPtr new_display)
: line_increment(2), cur_page_idx(0)
{
  game_display = new_display;
  user_prompt = std::make_shared<NullPrompt>();
}

Screen::~Screen()
{
  game_display->clear_screen();
}

// Do whatever work is necessary to initialize the Screen
void Screen::initialize()
{
  // Subclasses should always override this method.
}

void Screen::set_title_text_sid(const string& new_title_text_sid)
{
  title_text_sid = new_title_text_sid;
}

std::string Screen::get_title_text_sid() const
{
  return title_text_sid;
}

// Return the first option with the given option id, or a null OptionPtr
// if none is found.  While this is a shared_ptr, the shared_ptr is just
// used to indicate whether there is an option or not.  It points at a
// copy of the real option, to ensure immutability.
OptionPtr Screen::get_option(const int op_id)
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

// Display the contents of the Screen to the user via the DisplayPtr.
string Screen::display()
{
  bool done = false;
  string screen_selection;

  while (!done)
  {
    screen_selection = game_display->display_screen(*this);
    done = true;

    if (!screen_selection.empty())
    {
      CommandFactoryPtr command_factory = std::make_shared<ScreenCommandFactory>();
      KeyboardCommandMapPtr kb_command_map = std::make_shared<ScreenKeyboardCommandMap>();
      CommandPtr command = command_factory->create(String::to_int(screen_selection), kb_command_map->get_command_type(screen_selection));

      if (command != nullptr)
      {
        uint pn = get_current_page_number();
        string name = command->get_name();

        if (name == ScreenCommandKeys::NEXT_PAGE)
        {
          set_current_page_number(pn + 1);
        }
        else if (name == ScreenCommandKeys::PREVIOUS_PAGE)
        {
          set_current_page_number(pn - 1);
        }

        done = false;

        // We're going to create another Screen, because we've determined
        // we need to try changing the page.
        //
        // Destroy the current Screen.
        game_display->clear_screen();
      }
    }
  }

  return screen_selection;
}

// Display a prompt to the user, and get the user's response.
string Screen::prompt()
{
  string empty_str;
  return empty_str;
}

// Can't increment cnt in here because the ScreenComponentPtr may span
// multiple lines - e.g., an options component with several values.
//
// Return true if a new page was generated.
bool Screen::add_component(vector<ScreenComponentPtr>& current_screen, ScreenComponentPtr component, int& cnt)
{
  bool result = false;

  if (cnt >= LINES_DISPLAYABLE_AREA)
  {
    cnt = 0;

    add_page(current_screen);
    current_screen.clear();
    result = true;
  }

  current_screen.push_back(component);
  return result;
}

void Screen::add_page(const vector<ScreenComponentPtr>& new_page)
{
  components.push_back(new_page);
}

void Screen::set_prompt(PromptPtr new_prompt)
{
  user_prompt = new_prompt;
}

PromptPtr Screen::get_prompt() const
{
  return user_prompt;
}

vector<vector<ScreenComponentPtr>> Screen::get_components() const
{
  return components;
}

vector<ScreenComponentPtr> Screen::get_current_page() const
{
  return components.at(cur_page_idx);
}

// Get the line spacing.
uint Screen::get_line_increment() const
{
  return line_increment;
}

// Get the current page number, internally
uint Screen::get_cur_page_idx() const
{
  return cur_page_idx;
}

// Set the current page number, assuming sane input
void Screen::set_current_page_number(const uint new_page_number)
{
  if (new_page_number >= 1 && new_page_number <= components.size())
  {
    cur_page_idx = new_page_number-1;
  }
}

// Get the current page number, for external use (ie, idx 0 is pg. 1)
uint Screen::get_current_page_number() const
{
  return (cur_page_idx + 1);
}

// Get the total number of pages
uint Screen::get_num_pages() const
{
  return components.size();
}
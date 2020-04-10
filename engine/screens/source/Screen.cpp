#include <boost/algorithm/string.hpp>
#include "global_prototypes.hpp"
#include "Conversion.hpp"
#include "Screen.hpp"
#include "ScreenCommandFactory.hpp"
#include "ScreenCommandKeys.hpp"
#include "ScreenKeyboardCommandMap.hpp"
#include "TextFormatSpecifiers.hpp"

using namespace std;
using namespace boost::algorithm;

// Any base initialization for the Screen
Screen::Screen(DisplayPtr new_display)
: line_increment(2), cur_page_idx(0), lines_displayable_area(21)
{
  game_display = new_display;
  user_prompt = std::make_shared<NullPrompt>();
  lines_displayable_area = Screen::get_lines_displayable_area(new_display);
}

Screen::~Screen()
{
  game_display->clear_screen();
}

int Screen::get_lines_displayable_area(DisplayPtr display)
{
  int num_lines = 0;

  if (display != nullptr)
  {
    num_lines = std::max<int>(display->get_height() - 3, num_lines);
  }

  return num_lines;
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
      CommandFactoryPtr command_factory = std::make_unique<ScreenCommandFactory>();
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

bool Screen::add_options_component(std::vector<ScreenComponentPtr>& current_menu, OptionsComponentPtr options, int& cnt, int& current_option_id)
{
  bool new_page = add_component(current_menu, options, cnt, current_option_id);

  if (new_page)
  {
    vector<Option>& opt = options->get_options_ref();

    if (!opt.empty())
    {
      opt.at(opt.size()-1).set_id(current_option_id);
    }
  }

  return new_page;
}

// Can't increment cnt in here because the ScreenComponentPtr may span
// multiple lines - e.g., an options component with several values.
//
// Return true if a new page was generated.
bool Screen::add_component(vector<ScreenComponentPtr>& current_screen, ScreenComponentPtr component, int& cnt)
{
  int ignore = 0;
  return add_component(current_screen, component, cnt, ignore);
}

bool Screen::add_component(vector<ScreenComponentPtr>& current_screen, ScreenComponentPtr component, int& cnt, int& current_option_id)
{
  bool result = false;

  // We've gone over the max displayable area.  Add the current page to the
  // screen, and reset the line count and the option ID.
  if (cnt >= lines_displayable_area)
  {
    // Reset this to 1 so that when the component is pushed on to the new
    // screen, the counter will be reflective of what's actually there.
    cnt = 1;
    current_option_id = 0;

    add_page(current_screen);
    current_screen.clear();
    result = true;
  }

  current_screen.push_back(component);
  return result;
}

bool Screen::add_text(vector<ScreenComponentPtr>& text_screen, const vector<TextDisplayPair>& text, deque<Symbol>& symbols, const bool preserve_formatting, int& cnt)
{
  // Set the text components.
  for (const TextDisplayPair& line_pair : text)
  {
    Colour colour = line_pair.first;
    string text = line_pair.second;

    if (preserve_formatting == false)
    {
      trim_left(text);
      trim_right(text);
    }

    size_t sym_count = count_substrings(text, TextFormatSpecifiers::SYMBOL);
    vector<Symbol> tc_symbols;

    for (size_t i = 0; i < sym_count; i++)
    {
      if (!symbols.empty())
      {
        tc_symbols.push_back(symbols.front());
        symbols.pop_front();
      }
    }

    TextComponentPtr current_line = std::make_shared<TextComponent>(text, colour, tc_symbols);
    cnt++;

    add_component(text_screen, current_line, cnt);
  }

  return true;
}

bool Screen::can_add_component(const int cnt) const
{
  return (cnt < lines_displayable_area);
}

void Screen::add_page(const vector<ScreenComponentPtr>& new_page)
{
  components.push_back(new_page);
}

Prompt* Screen::get_prompt() const
{
  return user_prompt.get();
}

vector<vector<ScreenComponentPtr>> Screen::get_components() const
{
  return components;
}

vector<ScreenComponentPtr> Screen::get_current_page() const
{
  vector<ScreenComponentPtr> cur_page;

  if (!components.empty())
  {
    cur_page = components.at(cur_page_idx);
  }

  return cur_page;
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
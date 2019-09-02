#include <sstream>
#include "Display.hpp"
#include "Screen.hpp"
#include "Serialize.hpp"
#include "StringTable.hpp"

using namespace std;

// Draw the specified screen, full-screen.
string Display::display_screen(const Screen& current_screen)
{
  string result;

  MenuWrapper wrapper;
  setup_new_screen();

  int current_row = 0;
  int current_col = 0;

  // Display the header if the text is defined.  Some screens (like the quest list,
  // etc) will have this defined, while others (such as the new character-type
  // screens) will not.
  string title_text_sid = current_screen.get_title_text_sid();
  string header_text = StringTable::get(title_text_sid);

  // The title might not be an actual resource string, but instead an already-
  // formatted message.  Use that if the lookup is empty but the sid is not.
  if (!title_text_sid.empty() && header_text.empty())
  {
    header_text = title_text_sid;
  }

  uint num_pages = current_screen.get_num_pages();

  if (num_pages > 1)
  {
    ostringstream ss;

    ss << header_text << " (" << current_screen.get_current_page_number() << "/" << num_pages << ")";
    header_text = ss.str();
  }

  if (!header_text.empty())
  {
    display_header(header_text, current_row);

    // Always allow for some space between the title and the components of the
    // screen, regardless of what the screen has set for line spacing.
    current_row += 2;
  }

  vector<ScreenComponentPtr> components = current_screen.get_current_page();
  uint line_incr = current_screen.get_line_increment();

  uint csize = components.size();
  for (uint i = 0; i < csize; i++)
  {
    ScreenComponentPtr component = components.at(i);
    ComponentAlignment ca = component->get_spacing_after();

    // Check to see if we should override the screen's line increment value.
    if (ca.get_override_default())
    {
      line_incr = ca.get_value();
    }

    if (component)
    {
      TextComponentPtr tc = dynamic_pointer_cast<TextComponent>(component);

      if (tc != nullptr)
      {
        display_text_component(&current_row, &current_col, tc, line_incr);
      }
      else
      {
        OptionsComponentPtr oc = dynamic_pointer_cast<OptionsComponent>(component);

        if (oc != nullptr)
        {
          // Process the options...
          display_options_component(&current_row, &current_col, oc);

          // Add them so that the prompt processor knows about the options in this set.
          wrapper.add_options(oc);
        }
      }

      // After each line, check to see if we need to throw up a prompt because
      // of hitting the end of the screen, but only if there's still stuff to
      // display.
      if (current_row == (static_cast<int>(get_max_rows()) - 1) && (i != csize - 1))
      {
        get_prompt_value(current_screen, wrapper, current_row, current_col);

        refresh_and_clear_window();
        current_row = 0;
      }
    }
  }

  refresh_current_window();

  // Done!  Add an appropriate prompt.
  result = get_prompt_value(current_screen, wrapper, current_row, current_col);
  refresh_current_window();

  return result;
}

bool Display::serialize(ostream& stream) const
{
  Serialize::write_string_map(stream, display_properties);

  return true;
}

bool Display::deserialize(istream& stream)
{
  Serialize::read_string_map(stream, display_properties);

  return true;
}

void Display::set_properties(const map<string, string>& new_properties)
{
  display_properties = new_properties;
}

void Display::set_property(const string& property, const string& value)
{
  display_properties[property] = value;
}

bool Display::remove_property(const string& property)
{
  bool removed = false;
  auto p_it = display_properties.find(property);

  if (p_it != display_properties.end())
  {
    display_properties.erase(p_it);
    removed = true;
  }

  return removed;
}

string Display::get_property(const string& property) const
{
  string value;

  auto prop_it = display_properties.find(property);

  if (prop_it != display_properties.end())
  {
    value = prop_it->second;
  }

  return value;
}


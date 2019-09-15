#include <sstream>
#include "Conversion.hpp"
#include "Display.hpp"
#include "Game.hpp"
#include "Screen.hpp"
#include "Setting.hpp"
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

// Display the player data at the bottom of the screen
void Display::display(const DisplayStatistics& player_stats)
{
  Game& game = Game::instance();
  Settings& settings = game.get_settings_ref();

  string name = player_stats.get_name();
  string synopsis = player_stats.get_synopsis();

  pair<string, Colour> strength = player_stats.get_strength();
  pair<string, Colour> dexterity = player_stats.get_dexterity();
  pair<string, Colour> agility = player_stats.get_agility();
  pair<string, Colour> health = player_stats.get_health();
  pair<string, Colour> intelligence = player_stats.get_intelligence();
  pair<string, Colour> willpower = player_stats.get_willpower();
  pair<string, Colour> charisma = player_stats.get_charisma();

  string speed = player_stats.get_speed();

  string level = player_stats.get_level();
  string defence = player_stats.get_defence();

  pair<string, Colour> alignment = player_stats.get_alignment();

  string hit_points = player_stats.get_hit_points();
  Colour hit_points_colour = String::to_colour(settings.get_setting(Setting::DEFAULT_HP_COLOUR), Colour::COLOUR_WHITE);

  string arc_points = player_stats.get_arcana_points();
  Colour arc_points_colour = String::to_colour(settings.get_setting(Setting::DEFAULT_AP_COLOUR), Colour::COLOUR_WHITE);

  string map_depth = player_stats.get_map_depth();

  vector<pair<string, Colour>> status_ailments = player_stats.get_status_ailments();

  uint max_rows = static_cast<uint>(get_max_rows());
  unsigned int PLAYER_SYNOPSIS_START_ROW = max_rows - 3;
  unsigned int current_row = PLAYER_SYNOPSIS_START_ROW;
  unsigned int initial_row = current_row;
  unsigned int current_col = 0;
  bool can_print = true;

  // First, clear the synopsis.
  clear_to_bottom(PLAYER_SYNOPSIS_START_ROW);

  // Next, set the synopsis values
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, name, synopsis);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, synopsis, strength.first);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, strength.first, dexterity.first, strength.second);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, dexterity.first, agility.first, dexterity.second);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, agility.first, health.first, agility.second);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, health.first, intelligence.first, health.second);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, intelligence.first, willpower.first, intelligence.second);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, willpower.first, charisma.first, willpower.second);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, charisma.first, level, charisma.second);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, level, defence);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, defence, alignment.first);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, alignment.first, speed, alignment.second);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, speed, hit_points);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, hit_points, arc_points, hit_points_colour);
  if (can_print) can_print = display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, arc_points, map_depth, arc_points_colour);
  display_text(current_row, current_col, map_depth);

  // Last row: status ailments
  current_row = max_rows - 1;
  current_col = 0;

  for (uint x = 0; x < status_ailments.size(); x++)
  {
    pair<string, Colour> status_ailment = status_ailments.at(x);
    bool has_more = (x != (status_ailments.size() - 1));

    if (has_more)
    {
      pair<string, Colour> next_ailment = status_ailments.at(x + 1);

      if (can_print)
      {
        Colour colour = status_ailment.second;

        display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, status_ailment.first, next_ailment.first, colour);
      }
    }
    else
    {
      if (can_print)
      {
        Colour colour = status_ailment.second;
        enable_colour(colour);
        string sail = status_ailment.first;
        display_text(current_row, current_col, sail);
        disable_colour(colour);
      }
    }
  }
}

bool Display::display_statistic_and_update_row_and_column(const unsigned int initial_row, unsigned int* current_row, unsigned int* current_col, const string& current_stat, const string& next_stat, Colour print_colour)
{
  bool can_print = true;
  string stat = current_stat;
  enable_colour(print_colour);
  display_text(*current_row, *current_col, current_stat);
  can_print = update_synopsis_row_and_column(initial_row, current_row, current_col, current_stat, next_stat);
  disable_colour(print_colour);
  return can_print;
}

// Update the row/col for the player synopsis.  Return false if we've run out of space
// and can't print anything else.
bool Display::update_synopsis_row_and_column(const unsigned int initial_row, unsigned int* row, unsigned int* col, const string& previous_field, const string& next_field)
{
  bool can_update = true;
  int field_space = static_cast<uint>(get_field_space());
  unsigned int next_column_end = *col + previous_field.size() + field_space + next_field.size();
  uint max_cols = get_max_cols();
  uint max_rows = get_max_rows();

  *col = *col + previous_field.size() + field_space;

  if (next_column_end > max_cols - 1)
  {
    // We've gone over max cols.  Fine - but can we increment to the next row in the display?
    if (*row < max_rows - 2)
    {
      *col = 0;
      *row = *row + 1;
    }
    else
    {
      can_update = false;
    }
  }

  return can_update;
}

int Display::get_field_space() const
{
  return 2;
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


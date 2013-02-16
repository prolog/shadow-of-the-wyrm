#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "global_prototypes.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;

TextDisplayScreen::TextDisplayScreen(DisplayPtr new_display, const vector<string>& new_text) : Menu(new_display), text(new_text)
{
  // Set the line increment to 1, so that single-spacing between lines is
  // enforced.  Otherwise, things will look goofy.
  line_increment = 1;

  initialize();
}

void TextDisplayScreen::initialize()
{
  BOOST_FOREACH(string line, text)
  {
    TextComponentPtr current_line = boost::make_shared<TextComponent>(line);
    components.push_back(current_line);
  }
}

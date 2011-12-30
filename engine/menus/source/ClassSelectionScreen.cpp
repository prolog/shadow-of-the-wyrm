#include "ClassSelectionScreen.hpp"

#include <string>
#include "RaceSelectionScreen.hpp"
#include "Game.hpp"
#include "OptionsComponent.hpp"
#include "StringConstants.hpp"
#include "TextComponent.hpp"

using namespace std;

ClassSelectionScreen::ClassSelectionScreen(DisplayPtr new_display)
: Menu(new_display)
{
  initialize();
}

// Initialize the class selection screen.  Classes must have been read in, and set into the Game
// instance at this point.
//
// The Menu will return an int based on the user's selection.  This will map to a race_id, which will then map to a
// ClassPtr
void ClassSelectionScreen::initialize()
{
  Game* game_instance = Game::instance();
  ClassMap classes = game_instance->get_classes_ref();

  TextComponent* class_selection_text = new TextComponent(StringTable::get(TextKeys::SELECT_CLASS));

  // Each option represents a player-selectable class.
  OptionsComponent* options = new OptionsComponent();

  int current_id = 0;
  for (ClassMap::iterator classes_it = classes.begin(); classes_it != classes.end(); classes_it++)
  {
    string class_id = classes_it->first;
    ClassPtr current_class = classes_it->second;

    if (current_class && options)
    {
      Option current_option;
      current_option.set_id(current_id);
      current_option.set_description(StringTable::get(current_class->get_class_name_sid()));

      options->add_option(current_option);
// JCD FIXME      options->add_option_description(StringTable::get(current_class->get_class_short_description_sid()));
      options->add_option_description("");
      current_id++;
    }
  }

  components.push_back(class_selection_text);
  components.push_back(options);
}

#include <string>
#include "ClassSelectionScreen.hpp"
#include "RaceSelectionScreen.hpp"
#include "Game.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "TextComponent.hpp"
#include "TextKeys.hpp"

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
  Game& game_instance = Game::instance();
  ClassMap classes = game_instance.get_classes_ref();

  TextComponentPtr class_selection_text = std::make_shared<TextComponent>(StringTable::get(TextKeys::SELECT_CLASS));

  // Each option represents a player-selectable class.
  OptionsComponentPtr options = std::make_shared<OptionsComponent>();

  int current_id = 0;
  for (ClassMap::iterator classes_it = classes.begin(); classes_it != classes.end(); classes_it++)
  {
    string class_id = classes_it->first;
    ClassPtr current_class = classes_it->second;

    if (current_class && current_class->get_user_playable() && options)
    {
      Option current_option;
      current_option.set_id(current_id);
      current_option.set_description(StringTable::get(current_class->get_class_name_sid()));

      options->add_option(current_option);
      options->add_option_description("");
      current_id++;
    }
  }

  vector<MenuComponentPtr> cur_page;
  cur_page.push_back(class_selection_text);
  cur_page.push_back(options);

  add_page(cur_page);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_shared<Prompt>(PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = any_key_prompt;
}

#include "DeitySelectionScreen.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "TextKeys.hpp"

using namespace std;

DeitySelectionScreen::DeitySelectionScreen(DisplayPtr new_display, RacePtr selected_race)
: Screen(new_display), race(selected_race)
{
  initialize();
}

// Initialize the deity selection screen.  Deities must have been
// read in, and set into the Game object by this point.  As well,
// a valid RacePtr must have been provided to the constructor, so
// that we know what deities can be selected.
void DeitySelectionScreen::initialize()
{
  vector<ScreenComponentPtr> deity_screen;

  if (race)
  {
    Game& game_instance = Game::instance();
    DeityMap deities = game_instance.get_deities_ref();
    vector<string> deity_ids = race->get_initial_deity_ids();

    TextComponentPtr deity_selection_text = std::make_shared<TextComponent>(StringTable::get(TextKeys::SELECT_DEITY));
    OptionsComponentPtr options = std::make_shared<OptionsComponent>();
    int current_id = 0;
    
    for (const string& deity_id : deity_ids)
    {
      DeityMap::iterator d_it = deities.find(deity_id);
      
      if (d_it != deities.end())
      {
        DeityPtr deity = d_it->second;
        
        if (deity)
        {
          string deity_name  = StringTable::get(deity->get_name_sid());
          string deity_sdesc = StringTable::get(deity->get_short_description_sid());
          
          Option current_option;
          current_option.set_id(current_id);
          current_option.set_description(deity_name);
          
          options->add_option(current_option);
          options->add_option_description(deity_sdesc); 
          
          current_id++;
        }
        else
        {
          string error_msg = "Deity ID (" + deity_id + ") found, but DeityPtr is null.";
          Log::instance().log(error_msg);
        }
      }
      else
      {
        string error_msg = "Could not find deity_id: " + deity_id;
        Log::instance().log(error_msg);
      }
    }
    
    deity_screen.push_back(deity_selection_text);
    deity_screen.push_back(options);
  }

  add_page(deity_screen);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_shared<Prompt>(PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = any_key_prompt;
}

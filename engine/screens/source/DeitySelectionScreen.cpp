#include "DeitySelectionScreen.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "TextKeys.hpp"

using namespace std;

DeitySelectionScreen::DeitySelectionScreen(DisplayPtr new_display, Race* selected_race, const string& synop)
: Screen(new_display), race(selected_race), creature_synopsis(synop)
{
  initialize();
}

// Initialize the deity selection screen.  Deities must have been
// read in, and set into the Game object by this point.  As well,
// a valid Race* must have been provided to the constructor, so
// that we know what deities can be selected.
void DeitySelectionScreen::initialize()
{
  vector<ScreenComponentPtr> deity_screen;

  if (race)
  {
    Game& game_instance = Game::instance();
    const DeityMap& deities = game_instance.get_deities_cref();
    vector<string> deity_ids = race->get_initial_deity_ids();
    ostringstream synop;

    if (!creature_synopsis.empty())
    {
      synop << "[" << creature_synopsis << "]";
    }

    TextComponentPtr synopsis_text = std::make_shared<TextComponent>(synop.str());
    TextComponentPtr deity_selection_text = std::make_shared<TextComponent>(StringTable::get(TextKeys::SELECT_DEITY));
    OptionsComponentPtr options = std::make_shared<OptionsComponent>();
    int current_id = 0;
    
    for (const string& deity_id : deity_ids)
    {
      auto d_it = deities.find(deity_id);
      
      if (d_it != deities.end())
      {
        Deity& deity = *d_it->second;
        
        string deity_name  = StringTable::get(deity.get_name_sid());
        string deity_sdesc = StringTable::get(deity.get_short_description_sid());
          
        Option current_option;
        current_option.set_id(current_id);
        current_option.set_description(deity_name);
          
        options->add_option(current_option);
        options->add_option_description(deity_sdesc); 
          
        current_id++;
      }
      else
      {
        string error_msg = "DeitySelectionScreen::initialize - Could not find deity_id: " + deity_id;
        Log::instance().log(error_msg);
      }
    }

    Option godless_option;
    godless_option.set_id(current_id);
    godless_option.set_description(StringTable::get(DeityTextKeys::DEITY_GODLESS));

    options->add_option(godless_option);
    options->add_option_description("");

    current_id++;

    // Random selection (use '*')
    Option random_option;
    random_option.set_id(random_option.get_id_for_random());
    random_option.set_description(StringTable::get(TextKeys::RANDOM_SELECTION));

    options->add_option(random_option);
    options->add_option_description("");

    deity_screen.push_back(synopsis_text);
    deity_screen.push_back(deity_selection_text);
    deity_screen.push_back(options);
  }

  add_page(deity_screen);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_unique<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = std::move(any_key_prompt);
}

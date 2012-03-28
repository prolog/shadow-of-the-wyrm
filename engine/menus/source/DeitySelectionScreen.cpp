#include <boost/foreach.hpp>
#include "DeitySelectionScreen.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "OptionsComponent.hpp"
#include "StringConstants.hpp"

using namespace std;

DeitySelectionScreen::DeitySelectionScreen(DisplayPtr new_display, RacePtr selected_race)
: Menu(new_display), race(selected_race)
{
  initialize();
}

// Initialize the deity selection screen.  Deities must have been
// read in, and set into the Game object by this point.  As well,
// a valid RacePtr must have been provided to the constructor, so
// that we know what deities can be selected.
void DeitySelectionScreen::initialize()
{
  if (race)
  {
    Game* game_instance = Game::instance();
    DeityMap deities = game_instance->get_deities_ref();
    vector<string> deity_ids = race->get_initial_deity_ids();

    TextComponent* deity_selection_text = new TextComponent(StringTable::get(TextKeys::SELECT_DEITY));
    OptionsComponent* options = new OptionsComponent();
    int current_id = 0;
    
    BOOST_FOREACH(string deity_id, deity_ids)
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
          Log::instance()->log(error_msg);
        }
      }
      else
      {
        string error_msg = "Could not find deity_id: " + deity_id;
        Log::instance()->log(error_msg);
      }
    }
    
    components.push_back(deity_selection_text);
    components.push_back(options);
  }
}

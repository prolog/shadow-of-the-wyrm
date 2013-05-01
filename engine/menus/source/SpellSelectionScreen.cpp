#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "DescriberFactory.hpp"
#include "SpellSelectionScreen.hpp"
#include "Game.hpp"
#include "MenuTitleTextKeys.hpp"
#include "OptionsComponent.hpp"
#include "SpellcastingTextKeys.hpp"
#include "StringTable.hpp"
#include "TextComponent.hpp"
#include "TextKeys.hpp"

using namespace std;

const int SpellSelectionScreen::SPELLS_PER_PAGE = 18;

SpellSelectionScreen::SpellSelectionScreen(DisplayPtr new_display, CreaturePtr player /* should only be shown for player! */)
: Menu(new_display), creature(player)
{
  initialize();
}

string SpellSelectionScreen::get_selected_spell(const char selection) const
{
  string spell_id;

  map<char, string>::const_iterator selection_map_it = menu_selection_to_spell_id_map.find(selection);

  if (selection_map_it != menu_selection_to_spell_id_map.end())
  {
    spell_id = selection_map_it->second;
  }


  return spell_id;
}

// Show the spell selection screen.
void SpellSelectionScreen::initialize()
{
  // Set the menu title.
  title_text_sid = MenuTitleKeys::MENU_TITLE_MAGIC_SPELLS;

  // Go through the player's spells, and add them as options.
  int i = 0;
  if (creature)
  {
    OptionsComponentPtr options = boost::make_shared<OptionsComponent>();

    // Only show the value created by the SpellDescriber.
    options->set_show_option_descriptions(false);

    Game& game = Game::instance();
    SpellKnowledge& sk = creature->get_spell_knowledge_ref();
    SpellKnowledgeMap known_spells = sk.get_known_spells();
    const SpellMap& spells = game.get_spells_ref();

    BOOST_FOREACH(SpellKnowledgeMap::value_type& spell_pair, known_spells)
    {
      string spell_id = spell_pair.first;
      menu_selection_to_spell_id_map.insert(make_pair('a' + i, spell_id));

      if (sk.get_spell_knowledge(spell_id) > 0)
      {
        // Using the spell ID and a SpellDescriber, create text for the 
        // option shown in the UI.
        Spell spell = spells.find(spell_id)->second;
        IDescriberPtr describer = DescriberFactory::create_describer(creature, spell);
        string spell_desc = describer->describe();

        Option current_option;
        current_option.set_id(i);
        current_option.set_description(spell_desc);
          
        options->add_option(current_option);

        i++;

        if (i == SPELLS_PER_PAGE)
        {
          break;
        }
      }
    }

    components.push_back(options);
  }

  // Add the info prompt at the bottom of the screen.
  // Set the prompt
  PromptPtr spellcasting_prompt = boost::make_shared<Prompt>(PROMPT_LOCATION_LOWER_RIGHT);
  spellcasting_prompt->set_text_sid(SpellcastingTextKeys::SPELLCASTING_SCREEN_PROMPT);
  spellcasting_prompt->set_accept_any_input(true);
  user_prompt = spellcasting_prompt;
}

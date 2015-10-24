#include "DescriberFactory.hpp"
#include "SpellSelectionScreen.hpp"
#include "Game.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "OptionsComponent.hpp"
#include "SpellcastingTextKeys.hpp"
#include "StringTable.hpp"
#include "TextComponent.hpp"
#include "TextKeys.hpp"

using namespace std;

const int SpellSelectionScreen::SPELLS_PER_PAGE = 15;

SpellSelectionScreen::SpellSelectionScreen(DisplayPtr new_display, CreaturePtr player /* should only be shown for player! */)
: Screen(new_display), creature(player)
{
  initialize();
}

string SpellSelectionScreen::get_selected_spell(const char selection) const
{
  string spell_id;

  auto& selection_map = screen_selection_to_spell_id_map.at(get_cur_page_idx());
  map<char, string>::const_iterator selection_map_it = selection_map.find(selection);

  if (selection_map_it != selection_map.end())
  {
    spell_id = selection_map_it->second;
  }


  return spell_id;
}

// Show the spell selection screen.
void SpellSelectionScreen::initialize()
{
  // Set the screen title.
  title_text_sid = ScreenTitleTextKeys::SCREEN_TITLE_MAGIC_SPELLS;

  vector<ScreenComponentPtr> spell_screen;

  // Go through the player's spells, and add them as options.
  int i = 0;
  if (creature)
  {
    OptionsComponentPtr options = std::make_shared<OptionsComponent>();

    // Only show the value created by the SpellDescriber.
    options->set_show_option_descriptions(false);

    Game& game = Game::instance();
    SpellKnowledge& sk = creature->get_spell_knowledge_ref();
    SpellKnowledgeMap known_spells = sk.get_known_spells();
    const SpellMap& spells = game.get_spells_ref();
    std::map<char, std::string> selection_map;

    for (const SpellKnowledgeMap::value_type& spell_pair : known_spells)
    {
      string spell_id = spell_pair.first;
      selection_map.insert(make_pair('a' + i, spell_id));

      if (sk.get_spell_knowledge(spell_id).get_castings() > 0)
      {
        // Using the spell ID and a SpellDescriber, create text for the 
        // option shown in the UI.
        auto spell_it = spells.find(spell_id);

        if (spell_it == spells.end())
        {
          // Ignore a known spell if it doensn't exist, for whatever reason -
          // maybe it was incorrectly set by a script, doesn't exist anymore,
          // etc.
          continue;
        }

        Spell spell = spells.find(spell_id)->second;
        IDescriberPtr describer = DescriberFactory::create_describer(creature, spell);
        string spell_desc = describer->describe();

        Option current_option;
        current_option.set_id(i);
        current_option.set_description(spell_desc);
          
        options->add_option(current_option);

        i++;

        add_component(spell_screen, options, i);
        options = std::make_shared<OptionsComponent>();

        // If adding the component caused us to reset the page, be sure
        // to add the screen selection, clear the selection map, and recreate
        // the options component.
        if (i == 0)
        {
          screen_selection_to_spell_id_map.push_back(selection_map);
          selection_map.clear();
        }
      }
    }

    screen_selection_to_spell_id_map.push_back(selection_map);
    spell_screen.push_back(options);
    add_page(spell_screen);
  }

  // Add the info prompt at the bottom of the screen.
  // Set the prompt
  PromptPtr spellcasting_prompt = std::make_shared<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  spellcasting_prompt->set_text_sid(SpellcastingTextKeys::SPELLCASTING_SCREEN_PROMPT);
  spellcasting_prompt->set_accept_any_input(true);
  user_prompt = spellcasting_prompt;
}

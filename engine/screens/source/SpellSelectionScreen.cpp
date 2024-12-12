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

bool DefaultSpellScreenDisplayStrategy::display_spell(const Spell& /*spell*/) const
{
  return true;
}

SituationTypeSpellScreenDisplayStrategy::SituationTypeSpellScreenDisplayStrategy(const SpellSituationType new_sst)
: sst(new_sst)
{
}

bool SituationTypeSpellScreenDisplayStrategy::display_spell(const Spell& spell) const
{
  return (sst == spell.get_shape().get_spell_situation());
}

SpellSelectionScreen::SpellSelectionScreen(DisplayPtr new_display, CreaturePtr player /* should only be shown for player! */, SpellScreenDisplayStrategy* ssds)
: Screen(new_display), creature(player), strategy(ssds)
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
  Game& game = Game::instance();

  // Go through the player's spells, and add them as options.
  int i = 0;
  if (creature)
  {
    OptionsComponentPtr options = std::make_shared<OptionsComponent>();

    // Only show the value created by the SpellDescriber.
    options->set_show_option_descriptions(false);
    const SpellMap& spells = game.get_spells_ref();
    vector<Spell> display_spells = get_spells_in_display_order(spells);
    std::map<char, std::string> selection_map;

    for (const auto& spell : display_spells)
    {
      string spell_id = spell.get_spell_id();

      int line_number = i + 1;

      if (can_add_component(line_number) == false)
      {
        i = 0;
        line_number = 1;
        screen_selection_to_spell_id_map.push_back(selection_map);
        selection_map.clear();

        add_page(spell_screen);
        spell_screen.clear();
      }

      // Only add the spell to the display if it passes the castings/
      // filters/etc tests.
      selection_map.insert(make_pair('a' + i, spell_id));

      IDescriberPtr describer = DescriberFactory::create_describer(creature, spell);
      string spell_desc = describer->describe();

      Option current_option;
      current_option.set_id(i);
      current_option.set_description(spell_desc);

      options->add_option(current_option);

      add_component(spell_screen, options, line_number);
      options = std::make_shared<OptionsComponent>();

      i++;
    }

    screen_selection_to_spell_id_map.push_back(selection_map);
    spell_screen.push_back(options);
    add_page(spell_screen);
  }

  // Add the info prompt at the bottom of the screen.
  // Set the prompt
  PromptPtr spellcasting_prompt = std::make_unique<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  spellcasting_prompt->set_text_sid(SpellcastingTextKeys::SPELLCASTING_SCREEN_PROMPT);
  spellcasting_prompt->set_accept_any_input(true);
  user_prompt = std::move(spellcasting_prompt);
}

vector<Spell> SpellSelectionScreen::get_spells_in_display_order(const SpellMap& spells)
{
  vector<Spell> vsp;

  SpellKnowledge& sk = creature->get_spell_knowledge_ref();
  SpellKnowledgeMap known_spells = sk.get_known_spells();

  for (const SpellKnowledgeMap::value_type& spell_pair : known_spells)
  {
    string spell_id = spell_pair.first;

    if (sk.get_spell_knowledge(spell_id).get_castings() > 0)
    {
      auto spell_it = spells.find(spell_id);

      if (spell_it == spells.end())
      {
        // Ignore a known spell if it doensn't exist, for whatever reason -
        // maybe it was incorrectly set by a script, doesn't exist anymore,
        // etc.
        continue;
      }

      Spell spell = spells.find(spell_id)->second;

      if (strategy == nullptr || (strategy && !strategy->display_spell(spell)))
      {
        continue;
      }

      vsp.push_back(spell);
    }
  }

  std::sort(vsp.begin(), vsp.end(), sort_spells_for_display);

  return vsp;
}

bool SpellSelectionScreen::sort_spells_for_display(const Spell& s1, const Spell& s2)
{
  // First tiebreaker is by category.
  SkillType s1_cat = s1.get_magic_category();
  SkillType s2_cat = s2.get_magic_category();

  if (s1_cat != s2_cat)
  {
    return s1_cat < s2_cat;
  }
  else
  {
    // When AP cost and category are equal, the second tiebreaker is name.
    string s1_name = StringTable::get(s1.get_spell_name_sid());
    string s2_name = StringTable::get(s2.get_spell_name_sid());

    return s1_name < s2_name;
  }
}
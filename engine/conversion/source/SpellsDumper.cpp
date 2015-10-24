#include <sstream>
#include "Conversion.hpp"
#include "DescriberFactory.hpp"
#include "Game.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "SpellsDumper.hpp"
#include "StringTable.hpp"

using namespace std;

SpellsDumper::SpellsDumper(CreaturePtr new_creature, const uint new_max_cols)
: creature(new_creature), num_cols(new_max_cols)
{
}

string SpellsDumper::str() const
{
  return get_spells();
}

// Get the creature's spells.
string SpellsDumper::get_spells() const
{
  ostringstream ss;

  ss << String::centre(StringTable::get(ScreenTitleTextKeys::SCREEN_TITLE_MAGIC_SPELLS), num_cols) << endl << endl;

  int spell_count = 0;

  Game& game = Game::instance();
  SpellKnowledge& sk = creature->get_spell_knowledge_ref();
  SpellKnowledgeMap known_spells = sk.get_known_spells();
  const SpellMap& spells = game.get_spells_ref();

  for (const SpellKnowledgeMap::value_type& spell_pair : known_spells)
  {
    string spell_id = spell_pair.first;

    if (sk.get_spell_knowledge(spell_id).get_castings() > 0)
    {
      Spell spell = spells.find(spell_id)->second;
      IDescriberPtr describer = DescriberFactory::create_describer(creature, spell);
      string spell_desc = describer->describe();

      ss << spell_desc << endl;

      spell_count++;
    }
  }

  if (spell_count == 0)
  {
    ss << String::centre("-", num_cols) << endl;
  }

  return ss.str();
}

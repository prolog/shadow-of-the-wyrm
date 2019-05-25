#include "SpellbookCodexDescriber.hpp"
#include "Game.hpp"
#include "Spellbook.hpp"

using namespace std;

SpellbookCodexDescriber::SpellbookCodexDescriber(ItemPtr item)
: CodexDescriber(item)
{
}

string SpellbookCodexDescriber::describe_for_synopsis_line() const
{
  SpellbookPtr spellbook = dynamic_pointer_cast<Spellbook>(item);
  string desc;

  if (spellbook != nullptr)
  {
    string spell_id = spellbook->get_spell_id();
    const SpellMap spells = Game::instance().get_spells_ref();
    auto sp_details = spells.find(spell_id);

    if (sp_details != spells.end())
    {
      Skills skills;
      SkillPtr skill = skills.get_skill(sp_details->second.get_magic_category());

      if (skill != nullptr)
      {
        desc = StringTable::get(skill->get_skill_name_sid());
      }
    }
  }

  return desc;
}


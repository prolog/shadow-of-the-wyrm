#include "Game.hpp"
#include "MagicalCombatSkillMarker.hpp"
#include "SkillTypes.hpp"

using namespace std;

// When magic is cast, mark the Magic skill, and the category of the spell last cast.
vector<SkillType> MagicalCombatSkillMarker::get_marked_skills(CreaturePtr creature) const
{
  vector<SkillType> marked_skills{SKILL_GENERAL_MAGIC};

  Game& game = Game::instance();
  string most_recent_spell = creature->get_spell_knowledge_ref().get_most_recently_cast_spell_id();
  Spell spell = game.get_spells_ref().find(most_recent_spell)->second;
  SkillType magic_skill = spell.get_magic_category();
  marked_skills.push_back(magic_skill);

  return marked_skills;
}

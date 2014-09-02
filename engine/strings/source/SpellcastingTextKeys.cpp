#include "SpellcastingTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

SpellcastingTextKeys::SpellcastingTextKeys()
{
}

const string SpellcastingTextKeys::SPELLCASTING_NO_MAGICAL_KNOWLEDGE = "SPELLCASTING_NO_MAGICAL_KNOWLEDGE";
const string SpellcastingTextKeys::SPELLCASTING_UNAVAILABLE_ON_WORLD_MAP = "SPELLCASTING_UNAVAILABLE_ON_WORLD_MAP";
const string SpellcastingTextKeys::SPELLCASTING_SCREEN_PROMPT = "SPELLCASTING_SCREEN_PROMPT";
const string SpellcastingTextKeys::SPELLCASTING_INSUFFICIENT_POWER = "SPELLCASTING_INSUFFICIENT_POWER";
const string SpellcastingTextKeys::SPELLCASTING_BONUS_INCREASED = "SPELLCASTING_BONUS_INCREASED";
const string SpellcastingTextKeys::SPELLCASTING_NO_MAGIC_SKILL = "SPELLCASTING_NO_MAGIC_SKILL";
const string SpellcastingTextKeys::SPELLCASTING_SPELL_NOT_LEARNED = "SPELLCASTING_SPELL_NOT_LEARNED";
const string SpellcastingTextKeys::SPELLCASTING_UNFAMILIAR_CATEGORY = "SPELLCASTING_UNFAMILIAR_CATEGORY";
const string SpellcastingTextKeys::SPELLCASTING_READ_BOOK_PLAYER = "SPELLCASTING_READ_BOOK_PLAYER";
const string SpellcastingTextKeys::SPELLCASTING_READ_BOOK_MONSTER = "SPELLCASTING_READ_BOOK_MONSTER";
const string SpellcastingTextKeys::SPELLCASTING_READ_SCROLL_PLAYER = "SPELLCASTING_READ_SCROLL_PLAYER";
const string SpellcastingTextKeys::SPELLCASTING_READ_SCROLL_MONSTER = "SPELLCASTING_READ_SCROLL_MONSTER";
const string SpellcastingTextKeys::SPELLCASTING_READ_SPELLBOOK_PLAYER = "SPELLCASTING_READ_SPELLBOOK_PLAYER";
const string SpellcastingTextKeys::SPELLCASTING_READ_SPELLBOOK_MONSTER = "SPELLCASTING_READ_SPELLBOOK_MONSTER";

const string SpellcastingTextKeys::SPELLCASTING_TARGET_SELF_ABRV = "SPELLCASTING_TARGET_SELF_ABRV";
const string SpellcastingTextKeys::SPELLCASTING_BEAM_ABRV = "SPELLCASTING_BEAM_ABRV";
const string SpellcastingTextKeys::SPELLCASTING_REFLECTIVE_BEAM_ABRV = "SPELLCASTING_REFLECTIVE_BEAM_ABRV";
const string SpellcastingTextKeys::SPELLCASTING_CONE_ABRV = "SPELLCASTING_CONE_ABRV";
const string SpellcastingTextKeys::SPELLCASTING_BALL_ABRV = "SPELLCASTING_BALL_ABRV";
const string SpellcastingTextKeys::SPELLCASTING_CROSS_ABRV = "SPELLCASTING_CROSS_ABRV";
const string SpellcastingTextKeys::SPELLCASTING_SPELLBOOK_DESTRUCTION_MESSAGE = "SPELLCASTING_SPELLBOOK_DESTRUCTION_MESSAGE";

const string SpellcastingTextKeys::get_spellbook_destruction_message(const string& spellbook_desc)
{
  string destruction_message = StringTable::get(SpellcastingTextKeys::SPELLCASTING_SPELLBOOK_DESTRUCTION_MESSAGE);

  boost::replace_first(destruction_message, "%s", spellbook_desc);
  destruction_message[0] = toupper(destruction_message[0]);

  return destruction_message;
}
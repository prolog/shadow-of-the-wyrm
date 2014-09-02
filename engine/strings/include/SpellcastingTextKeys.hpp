#pragma once
#include <string>

class SpellcastingTextKeys
{
  public:
    static const std::string SPELLCASTING_NO_MAGICAL_KNOWLEDGE;
    static const std::string SPELLCASTING_UNAVAILABLE_ON_WORLD_MAP;
    static const std::string SPELLCASTING_SCREEN_PROMPT;
    static const std::string SPELLCASTING_INSUFFICIENT_POWER;
    static const std::string SPELLCASTING_BONUS_INCREASED;
    static const std::string SPELLCASTING_NO_MAGIC_SKILL;
    static const std::string SPELLCASTING_SPELL_NOT_LEARNED;
    static const std::string SPELLCASTING_UNFAMILIAR_CATEGORY;
    static const std::string SPELLCASTING_READ_BOOK_PLAYER;
    static const std::string SPELLCASTING_READ_BOOK_MONSTER;
    static const std::string SPELLCASTING_READ_SCROLL_PLAYER;
    static const std::string SPELLCASTING_READ_SCROLL_MONSTER;
    static const std::string SPELLCASTING_READ_SPELLBOOK_PLAYER;
    static const std::string SPELLCASTING_READ_SPELLBOOK_MONSTER;
    
    // Range abbreviation SIDs
    static const std::string SPELLCASTING_TARGET_SELF_ABRV;
    static const std::string SPELLCASTING_BEAM_ABRV;
    static const std::string SPELLCASTING_REFLECTIVE_BEAM_ABRV;
    static const std::string SPELLCASTING_CONE_ABRV;
    static const std::string SPELLCASTING_BALL_ABRV;
    static const std::string SPELLCASTING_CROSS_ABRV;

    static const std::string get_spellbook_destruction_message(const std::string& spellbook_desc_sid);

  protected:
    static const std::string SPELLCASTING_SPELLBOOK_DESTRUCTION_MESSAGE;

    SpellcastingTextKeys();
};

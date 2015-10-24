#include "CharacterDumpAction.hpp"
#include "CharacterDumper.hpp"
#include "Conversion.hpp"
#include "FileWriter.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "TextDisplayScreen.hpp"
#include "TextMessages.hpp"

using namespace std;

CharacterDumpAction::CharacterDumpAction()
{
}

ActionCostValue CharacterDumpAction::dump_character(CreaturePtr creature)
{
  if (creature != nullptr)
  {
    Game& game = Game::instance();
    string char_title_sid = ScreenTitleTextKeys::SCREEN_TITLE_CHARACTER_DETAILS;
    CharacterDumper dumper(creature);
    vector<string> char_text = String::tokenize(dumper.str(), "\n", true);

    vector<TextDisplayPair> char_details_text;
    string last_str;

    for (const string& str : char_text)
    {
      // Ensure that the newlines from the end of a line of text aren't added as separate
      // strings, or else the text will have lots of extra newlines and look bad.
      if (str != "\n" || last_str.empty())
      {
        char_details_text.push_back(make_pair(Colour::COLOUR_WHITE, str));
      }

      last_str = str;
    }

    TextDisplayScreen tds(game.get_display(), char_title_sid, char_details_text);
    tds.display();
  }

  return get_action_cost_value(creature);
}

void CharacterDumpAction::dump_character_to_file(CreaturePtr creature)
{
  if (creature)
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature->get_is_player());
    string name = creature->get_name();
    string dump_message = TextMessages::get_dumping_character_message(name);
    
    CharacterDumper dumper(creature);
    FileWriter file(creature->get_name());
    
    file.write(dumper.str());
    
    manager.add_new_message(dump_message);
    manager.send();
  }
}


ActionCostValue CharacterDumpAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}

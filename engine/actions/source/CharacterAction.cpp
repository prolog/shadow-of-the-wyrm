#include "CharacterAction.hpp"
#include "CharacterDumper.hpp"
#include "Conversion.hpp"
#include "FileWriter.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "TextDisplayScreen.hpp"
#include "TextMessages.hpp"

using namespace std;

CharacterAction::CharacterAction()
{
}

ActionCostValue CharacterAction::display_character(CreaturePtr creature)
{
  if (creature != nullptr)
  {
    Game& game = Game::instance();
    string char_title_sid = ScreenTitleTextKeys::SCREEN_TITLE_CHARACTER_DETAILS;
    CharacterDumper dumper(creature);
    vector<string> char_text = String::tokenize(dumper.str(), "\n", true);

    vector<TextDisplayPair> char_details_text;

    for (const string& str : char_text)
    {
      if (str != "\n")
      {
        char_details_text.push_back(make_pair(Colour::COLOUR_WHITE, str));
      }
    }

    TextDisplayScreen tds(game.get_display(), char_title_sid, char_details_text, true);
    tds.display();
  }

  return get_action_cost_value(creature);
}

ActionCostValue CharacterAction::dump_character(CreaturePtr creature)
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

  return get_action_cost_value(creature);
}


ActionCostValue CharacterAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}

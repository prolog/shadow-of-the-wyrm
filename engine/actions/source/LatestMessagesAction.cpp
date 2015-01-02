#include <vector>
#include "Game.hpp"
#include "LatestMessagesAction.hpp"
#include "MessageManagerFactory.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextDisplayScreen.hpp"
#include "TextKeys.hpp"

using namespace std;

ActionCostValue LatestMessagesAction::latest_messages(CreaturePtr creature)
{
  Game& game = Game::instance();
  string title_sid = TextKeys::LATEST_MESSAGES;
  vector<TextDisplayPair> buffer_text;

  MessageBuffer mb = MessageManagerFactory::instance().get_message_buffer();

  size_t num_msgs = mb.size();

  for (size_t i = 0; i < num_msgs; i++)
  {
    string msg = mb.get_message(i);

    TextDisplayFormatter tdf;
    vector<string> msg_formatted = tdf.format_text(msg);

    for (const string& msg_line : msg_formatted)
    {
      TextDisplayPair msg_history_line = make_pair(Colour::COLOUR_WHITE, msg_line);
      buffer_text.push_back(msg_history_line);
    }
  }

  TextDisplayScreen tds(game.get_display(), title_sid, buffer_text);
  tds.display();

  return get_action_cost_value(creature);
}

ActionCostValue LatestMessagesAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}

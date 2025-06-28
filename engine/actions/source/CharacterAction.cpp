#include <chrono>
#include <boost/algorithm/string.hpp>
#include "CharacterAction.hpp"
#include "CharacterDumper.hpp"
#include "Conversion.hpp"
#include "Environment.hpp"
#include "FileWriter.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextDisplayScreen.hpp"
#include "TextMessages.hpp"
#include "TextKeys.hpp"

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
    TextDisplayFormatter tdf(true);

    for (const string& str : char_text)
    {
      if (str != "\n")
      {
        if (str.empty())
        {
          char_details_text.push_back(make_pair(Colour::COLOUR_WHITE, str));
        }
        else
        {
          vector<string> formatted_line = tdf.format_text(boost::algorithm::trim_right_copy(str));

          for (const string& line : formatted_line)
          {
            char_details_text.push_back(make_pair(Colour::COLOUR_WHITE, line));
          }
        }
      }
    }

    TextDisplayScreen tds(game.get_display(), char_title_sid, char_details_text, true);
    tds.display();
  }

  return get_action_cost_value(creature);
}

ActionCostValue CharacterAction::dump_character(CreaturePtr creature, const CharacterDumpType cdt)
{
  if (creature)
  {
    IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature->get_is_player());
    string name = creature->get_name();

    Settings& settings = Game::instance().get_settings_ref();
    auto cur_time = std::chrono::system_clock::now();

    string dumpdata_dir = Environment::get_syschardump_directory(&settings);

    if (cdt == CharacterDumpType::CHARACTER_DUMP_USER_INITIATED)
    {
      dumpdata_dir = Environment::get_userdata_directory(&settings);

      string dump_message = TextMessages::get_dumping_character_message(name, dumpdata_dir);
      manager.add_new_message(dump_message);
      manager.send();
    }

    CharacterDumper dumper(creature);
    string file_contents = dumper.str();
    string fname = dumpdata_dir + name + ".txt";
    FileWriter file(fname);
    
    bool created_file = file.write(file_contents);

    if (!created_file)
    {
      ostringstream fns;
      fns << dumpdata_dir << name << "_" << std::chrono::system_clock::to_time_t(cur_time) << ".txt";
      string new_file_name = fns.str();
      file.set_file_name(new_file_name);
      created_file = file.write(file_contents);

      if (!created_file)
      {
        manager.add_new_message(StringTable::get(TextKeys::DUMPING_CHARACTER_FAILED) + " - " + new_file_name);
        manager.send();
      }
    }    
  }

  return get_action_cost_value(creature);
}


ActionCostValue CharacterAction::get_action_cost_value(CreaturePtr /* creature */) const
{
  return 0;
}

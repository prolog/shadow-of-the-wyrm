#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "HelpCommandFactory.hpp"
#include "HelpCommandProcessor.hpp"
#include "HelpKeyboardCommandMap.hpp"
#include "HelpScreen.hpp"
#include "HelpAction.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;

HelpAction::HelpAction()
{
}

ActionCostValue HelpAction::help(CreaturePtr creature) const
{
  CreaturePtr nullc;
  ActionCostValue action_cost_value = 0;

  DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
  CommandFactoryPtr command_factory = std::make_shared<HelpCommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_shared<HelpKeyboardCommandMap>();
  Game& game = Game::instance();

  if (decision_strategy)
  {
    while (action_cost_value > -1)
    {
      HelpScreen hs(game.get_display());
      string display_s = hs.display();
      int input = display_s.at(0);
      char screen_selection = display_s.at(0);

      CommandPtr help_command = decision_strategy->get_nonmap_decision(false, creature->get_id(), command_factory, kb_command_map, &input);
      action_cost_value = HelpCommandProcessor::process(creature, help_command);
    }
  }

  return get_action_cost_value(nullc);
}

ActionCostValue HelpAction::keybindings() const
{
  CreaturePtr null_c;

  Game& game = Game::instance();

  TextDisplayFormatter tdf;
  vector<string> kb_formatted = tdf.format_text(StringTable::get(ActionTextKeys::ACTION_KEYBINDINGS), Screen::LINES_DISPLAYABLE_AREA);
  vector<TextDisplayPair> kb_text;

  for (size_t i = 0; i < kb_formatted.size(); i++)
  {
    TextDisplayPair kb_line = make_pair(Colour::COLOUR_WHITE, kb_formatted.at(i));
    kb_text.push_back(kb_line);
  }

  TextDisplayScreen tds(game.get_display(), ScreenTitleTextKeys::SCREEN_TITLE_KEYBINDINGS, kb_text, true);
  tds.display();

  return get_action_cost_value(null_c);
}

ActionCostValue HelpAction::introduction_roguelikes() const
{
  return display_text(ScreenTitleTextKeys::SCREEN_TITLE_INTRODUCTION_ROGUELIKES, ActionTextKeys::ACTION_INTRODUCTION_ROGUELIKES, false);
}

ActionCostValue HelpAction::game_history() const
{
  return display_text(ScreenTitleTextKeys::SCREEN_TITLE_SOTW_HISTORY, ActionTextKeys::ACTION_SOTW_HISTORY, false);
}

ActionCostValue HelpAction::strategy_basics() const
{
  return display_text(ScreenTitleTextKeys::SCREEN_TITLE_STRATEGY_BASICS, ActionTextKeys::ACTION_STRATEGY_BASICS, false);
}

ActionCostValue HelpAction::display_text(const string& title_sid, const string& text_sid, const bool maintain_formatting) const
{
  CreaturePtr null_c;

  Game& game = Game::instance();

  TextDisplayFormatter tdf;
  vector<string> kb_formatted = tdf.format_text(StringTable::get(text_sid));
  vector<TextDisplayPair> td_text;

  for (size_t i = 0; i < kb_formatted.size(); i++)
  {
    TextDisplayPair td_line = make_pair(Colour::COLOUR_WHITE, kb_formatted.at(i));
    td_text.push_back(td_line);
  }

  TextDisplayScreen tds(game.get_display(), title_sid, td_text, false);
  tds.display();

  return get_action_cost_value(null_c);
}


ActionCostValue HelpAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}


#include "AgeSelectionScreen.hpp"
#include "ColourTextKeys.hpp"
#include "CreatureFeatures.hpp"
#include "TextComponent.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "StringTable.hpp"
#include "TextMessages.hpp"

using namespace std;

AgeSelectionScreen::AgeSelectionScreen(DisplayPtr new_display, const string& synopsis, const int min_select_age, const int max_select_age)
: Screen(new_display), creature_synopsis(synopsis), min_age(min_select_age), max_age(max_select_age)
{
  initialize();
}

void AgeSelectionScreen::initialize()
{
  vector<ScreenComponentPtr> age_screen;
  TextComponentPtr synopsis = std::make_shared<TextComponent>("[" + creature_synopsis + "]");
  age_screen.push_back(synopsis);
  add_page(age_screen);

  user_prompt = std::make_unique<TextPrompt>();
  user_prompt->set_text_sid(TextMessages::get_select_age_message(min_age, max_age));
}

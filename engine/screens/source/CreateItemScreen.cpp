#include "CreateItemScreen.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "ItemProperties.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "ScreenTitleTextKeys.hpp"

using namespace std;

CreateItemScreen::CreateItemScreen(DisplayPtr new_display, const SkillType skill)
: Screen(new_display), filter_skill(skill)
{
  initialize();
}

// From the Game, gets a list of items that can be created using the
// given filter_skill, displaying each as an option.
//
// The assumption is that the calling code has done all the necessary work
// to check for the correct components, etc., for the particular skill
// being used.
void CreateItemScreen::initialize()
{
  title_text_sid = ScreenTitleTextKeys::SCREEN_TITLE_CREATE_ITEM;
  vector<ItemPtr> craftable_items = get_craftable_items();

  // Add an option for each craftable item.
  vector<ScreenComponentPtr> create_item_screen;
  OptionsComponentPtr options = std::make_shared<OptionsComponent>();
  int current_id = 0;

  // The assumption is that there are a small number of craftable launchers -
  // easily enough to fit on a page.  If this assumption changes, the code below
  // will need to be reworked.
  for (ItemPtr item : craftable_items)
  {
    if (item != nullptr)
    {
      string base_id = item->get_base_id();

      Option current_option;
      current_option.set_external_id(base_id);
      current_option.set_id(current_id);
      current_option.set_description(StringTable::get(item->get_description_sid()));

      options->add_option(current_option);
      current_id++;
    }
  }

  create_item_screen.push_back(options);
  add_page(create_item_screen);

  // Create the prompt
  PromptPtr ci_prompt = std::make_shared<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  ci_prompt->set_accept_any_input(true);
  ci_prompt->set_text_sid(PromptTextKeys::PROMPT_CREATE_ITEM);
  user_prompt = ci_prompt;
}

vector<ItemPtr> CreateItemScreen::get_craftable_items()
{
  Game& game = Game::instance();
  const ItemMap items = game.get_items_ref();
  vector<ItemPtr> craftable_items;

  for (const auto& item_pair : items)
  {
    ItemPtr item = item_pair.second;

    if (item != nullptr)
    {
      string create_skill_s = item->get_additional_property(ItemProperties::ITEM_PROPERTIES_CREATION_SKILL);

      if (!create_skill_s.empty() && static_cast<SkillType>(String::to_int(create_skill_s)) == filter_skill)
      {
        craftable_items.push_back(item);
      }
    }
  }

  return craftable_items;
}
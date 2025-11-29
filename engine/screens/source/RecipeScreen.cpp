#include "Game.hpp"
#include "RecipeScreen.hpp"
#include "PromptTextKeys.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

RecipeScreen::RecipeScreen(DisplayPtr new_display, const Recipes& new_recipes, CreaturePtr new_creature)
: Screen(new_display), recipes(new_recipes), brewing_creature(new_creature)
{
  initialize();
}

void RecipeScreen::initialize()
{
  vector<ScreenComponentPtr> recipe_screen;
  title_text_sid = ScreenTitleTextKeys::SCREEN_TITLE_RECIPES;
  vector<Recipe> recs = recipes.get_recipes(brewing_creature);
  int cnt = 0;

  OptionsComponentPtr options = std::make_shared<OptionsComponent>();
  options->set_show_option_descriptions(false);

  const ItemMap& items = Game::instance().get_items_ref();

  if (brewing_creature != nullptr)
  {
    // Recipes line up with the vector of recipes the creature can potentially
    // brew. Some of these might be disabled, in the case where the creature
    // doesn't have the necessary ingredients.
    for (const Recipe& r : recs)
    {
      Option current_option;
      current_option.set_id(cnt++);

      string desc = "?";
      auto i_it = items.find(r.get_item_id());
      if (i_it != items.end())
      {
        desc = StringTable::get(i_it->second->get_description_sid());
      }

      current_option.set_description(desc);
      current_option.set_enabled(brewing_creature->get_inventory()->has_items_for_recipe(r));

      options->add_option(current_option);
    }
  }

  recipe_screen.push_back(options);
  add_page(recipe_screen);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_unique<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_accept_any_input(true);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_RECIPE);
  user_prompt = std::move(any_key_prompt);
}
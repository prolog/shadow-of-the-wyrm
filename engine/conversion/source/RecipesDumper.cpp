#include "Conversion.hpp"
#include "Game.hpp"
#include "RecipesDumper.hpp"
#include "ActionTextKeys.hpp"
#include "TextKeys.hpp"

using namespace std;

RecipesDumper::RecipesDumper(CreaturePtr new_creature, const Recipes& new_recipes, const uint new_num_cols)
: creature(new_creature), recipes(new_recipes), num_cols(new_num_cols)
{
}

string RecipesDumper::str() const
{
  Game& game = Game::instance();
  const ItemMap& items = game.get_items_ref();

  vector<Recipe> recs = recipes.get_recipes(creature);
  ostringstream ss;

  ss << String::centre(StringTable::get(TextKeys::RECIPES), num_cols) << endl << endl;

  if (recs.empty())
  {
    ss << String::centre("-", num_cols);
  }
  else
  {
    for (const auto& rec : recs)
    {
      Skill* skill = creature->get_skills().get_skill(rec.get_skill());
      auto i_it = items.find(rec.get_item_id());

      if (i_it != items.end() && i_it->second != nullptr && skill != nullptr)
      {
        ss << StringTable::get(i_it->second->get_description_sid()) << endl;

        ss << " - " << StringTable::get(TextKeys::SKILL_REQUIRED) << ": " << StringTable::get(skill->get_skill_name_sid()) << " " << rec.get_skill_required() << endl;

        vector<Ingredient> ingredients = rec.get_ingredients();

        if (!ingredients.empty())
        {
          ss << " - " << StringTable::get(ActionTextKeys::ACTION_BREWING_INGREDIENTS) << ": ";

          for (size_t i = 0; i < ingredients.size(); i++)
          {
            Ingredient ingr = ingredients.at(i);
            auto ingr_it = items.find(ingr.get_id());

            if (ingr_it != items.end())
            {
              ss << StringTable::get(ingr_it->second->get_description_sid()) << " (" << ingr.get_quantity() << ")";

              if (i < (ingredients.size() - 1))
              {
                ss << ", ";
              }
            }
          }

          ss << endl << endl;
        }
      }
    }
  }

  return ss.str();
}

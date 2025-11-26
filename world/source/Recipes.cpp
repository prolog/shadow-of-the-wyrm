#include "Recipes.hpp"
#include "Serialize.hpp"

using namespace std;

Recipes::Recipes()
{
}

Recipes::Recipes(const RecipesType& new_recipes)
: recipes(new_recipes)
{
}

Recipes::~Recipes()
{
}

bool Recipes::operator==(const Recipes& r2) const
{
  return (recipes == r2.recipes);
}

void Recipes::add(const Recipe& r)
{
  recipes[r.get_skill()][r.get_skill_required()][r.get_id()] = r;
}

vector<Recipe> Recipes::get_recipes(CreaturePtr creature) const
{
  vector<Recipe> rec;

  for (const auto& sr_pair : recipes)
  {
    for (const auto& ir_pair : sr_pair.second)
    {
      bool add_rec = true;

      if (creature != nullptr && creature->get_skills().get_value(sr_pair.first) < ir_pair.first)
      {
        add_rec = false;
      }

      if (add_rec)
      {
        for (const auto& kvr_pair : ir_pair.second)
        {
          rec.push_back(kvr_pair.second);
        }
      }
    }
  }

  return rec;
}

RecipesType& Recipes::get_recipes_ref()
{
  return recipes;
}

bool Recipes::serialize(std::ostream& stream) const
{
  Serialize::write_size_t(stream, recipes.size());
  for (const auto& rs_pair : recipes)
  {
    Serialize::write_enum(stream, rs_pair.first);
    Serialize::write_size_t(stream, rs_pair.second.size());

    for (const auto& rd_pair : rs_pair.second)
    {
      Serialize::write_int(stream, rd_pair.first);
      size_t num_recipes_at_level = rd_pair.second.size();
      Serialize::write_size_t(stream, num_recipes_at_level);

      for (const auto& sr_pair : rd_pair.second)
      {
        string id = sr_pair.first;
        Recipe r = sr_pair.second;

        Serialize::write_string(stream, id);
        r.serialize(stream);
      }
    }
  }
  
  return true;
}

bool Recipes::deserialize(std::istream& stream)
{
  recipes.clear();

  size_t recipes_sz = 0;
  Serialize::read_size_t(stream, recipes_sz);
  for (size_t i = 0; i < recipes_sz; i++)
  {
    SkillType recipe_skill = SkillType::SKILL_UNDEFINED;
    Serialize::read_enum(stream, recipe_skill);

    size_t skill_recipe_sz = 0;
    Serialize::read_size_t(stream, skill_recipe_sz);

    for (size_t j = 0; j < skill_recipe_sz; j++)
    {
      int skill_val = 0;
      Serialize::read_int(stream, skill_val);

      size_t num_recipes_at_level = 0;
      Serialize::read_size_t(stream, num_recipes_at_level);

      for (size_t k = 0; k < num_recipes_at_level; k++)
      {
        string r_id;
        Serialize::read_string(stream, r_id);

        Recipe r;
        r.deserialize(stream);

        recipes[recipe_skill][skill_val][r.get_id()] = r;
      }
    }
  }
  
  return true;
}

ClassIdentifier Recipes::internal_class_identifier() const
{
	return ClassIdentifier::CLASS_ID_RECIPES;
}

#ifdef UNIT_TESTS
#include "unit_tests/Recipes_test.cpp"
#endif

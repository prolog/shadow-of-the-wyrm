#include "CreateItemScreen.hpp"
#include "OptionsComponent.hpp"

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
}


#include "ClassManager.hpp"
#include "Game.hpp"

using std::string;

ClassManager::ClassManager()
{
}

ClassPtr ClassManager::get_class(const string& class_id)
{
  ClassPtr cur_class;

  Game* game = Game::instance();

  if (game)
  {
    ClassMap classes = game->get_classes_ref();
    cur_class = classes[class_id];
  }

  return cur_class;
}

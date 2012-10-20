#pragma once
#include <map>
#include "Menu.hpp"

class LoadGameScreen : public Menu
{
  public:
    LoadGameScreen(DisplayPtr display);

  protected:
    void initialize();

    std::map<std::string, std::string> menu_selection_to_filename_map;
};


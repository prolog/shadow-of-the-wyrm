#pragma once
#include <map>
#include "Menu.hpp"
#include "Display.hpp"

class ClassSelectionScreen : public Menu
{
  public:
    ClassSelectionScreen(DisplayPtr display);

  protected:
    void initialize();

    std::map<int, std::string> menu_selection_to_class_id_map;
};

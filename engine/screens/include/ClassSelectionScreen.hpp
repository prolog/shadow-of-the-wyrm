#pragma once
#include <map>
#include "Screen.hpp"
#include "Display.hpp"

class ClassSelectionScreen : public Screen
{
  public:
    ClassSelectionScreen(DisplayPtr display);

  protected:
    void initialize() override;

    std::map<int, std::string> screen_selection_to_class_id_map;
};

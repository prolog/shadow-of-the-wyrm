#pragma once
#include "Menu.hpp"
#include "Display.hpp"

class SexSelectionScreen : public Menu
{
  public:
    SexSelectionScreen(DisplayPtr display);

  protected:
    void initialize() override;
};

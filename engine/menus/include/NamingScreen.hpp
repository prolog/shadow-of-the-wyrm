#pragma once
#include "Display.hpp"
#include "Menu.hpp"

class NamingScreen : public Menu
{
  public:
    NamingScreen(DisplayPtr current_display);

  protected:
    void initialize();
};

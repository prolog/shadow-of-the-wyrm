#pragma once
#include "Menu.hpp"

class WelcomeScreen : public Menu
{
  public:
    WelcomeScreen(DisplayPtr display);

  protected:
    void initialize();
};

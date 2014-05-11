#pragma once
#include "Screen.hpp"

class WelcomeScreen : public Screen
{
  public:
    WelcomeScreen(DisplayPtr display);

  protected:
    void initialize() override;
};

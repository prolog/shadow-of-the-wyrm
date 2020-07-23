#pragma once
#include "Screen.hpp"
#include "Display.hpp"

class OrderScreen : public Screen
{
  public:
    OrderScreen(DisplayPtr display);

  protected:
    void initialize() override;
};

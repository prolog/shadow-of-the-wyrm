#pragma once
#include "Screen.hpp"
#include "Display.hpp"

class SkinSelectionScreen : public Screen
{
  public:
    SkinSelectionScreen(DisplayPtr display);

  protected:
    void initialize() override;
};

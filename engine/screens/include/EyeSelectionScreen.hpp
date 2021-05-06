#pragma once
#include "Screen.hpp"
#include "Display.hpp"

class EyeSelectionScreen : public Screen
{
  public:
    EyeSelectionScreen(DisplayPtr display);

  protected:
    void initialize() override;
};

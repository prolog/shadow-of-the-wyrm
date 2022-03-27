#pragma once
#include "Screen.hpp"
#include "Display.hpp"

class AgeSelectionScreen : public Screen
{
  public:
    AgeSelectionScreen(DisplayPtr display, const std::string& synopsis, const int min_select_age, const int max_select_age);

  protected:
    void initialize() override;

    const std::string creature_synopsis;
    const int min_age;
    const int max_age;
};

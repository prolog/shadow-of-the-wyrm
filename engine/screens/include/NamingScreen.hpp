#pragma once
#include <string>
#include "Display.hpp"
#include "Screen.hpp"

class NamingScreen : public Screen
{
  public:
    NamingScreen(DisplayPtr current_display, const std::string& new_warning_message);

  protected:
    void initialize() override;

    std::string warning_message;
};

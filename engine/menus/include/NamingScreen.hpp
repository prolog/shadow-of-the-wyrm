#pragma once
#include <string>
#include "Display.hpp"
#include "Menu.hpp"

class NamingScreen : public Menu
{
  public:
    NamingScreen(DisplayPtr current_display, const std::string& new_warning_message);

  protected:
    void initialize();

    std::string warning_message;
};

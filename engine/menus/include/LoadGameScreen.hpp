#pragma once
#include <map>
#include "Menu.hpp"

class LoadGameScreen : public Menu
{
  public:
    LoadGameScreen(DisplayPtr display);

    std::string get_file_name(const std::string& option) const;

protected:
    void initialize() override;

    std::map<std::string, std::string> menu_selection_to_filename_map;
};


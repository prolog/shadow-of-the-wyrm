#pragma once
#include <map>
#include "Screen.hpp"

class LoadGameScreen : public Screen
{
  public:
    LoadGameScreen(DisplayPtr display);

    std::string get_file_name(const std::string& option) const;

protected:
    void initialize() override;

    std::map<std::string, std::string> screen_selection_to_filename_map;
};


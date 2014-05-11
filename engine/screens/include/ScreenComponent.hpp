#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Colours.hpp"

class ScreenComponent
{
  public:
    ScreenComponent();
    ScreenComponent(const std::string& new_text);
    ScreenComponent(const std::string& new_text, const Colour new_colour);

    virtual void set_text(const std::vector<std::pair<std::string, Colour>>& new_text);
    virtual void add_text(const std::string& new_text);
    virtual void add_text(const std::string& new_text, const Colour new_colour);
    virtual std::vector<std::pair<std::string, Colour>> get_text() const;

  protected:
    std::vector<std::pair<std::string, Colour>> text;
};

typedef std::shared_ptr<ScreenComponent> ScreenComponentPtr;

#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Colours.hpp"
#include "ComponentAlignment.hpp"

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

    void set_spacing_after(const ComponentAlignment& new_component_alignment);
    ComponentAlignment get_spacing_after() const;

  protected:
    std::vector<std::pair<std::string, Colour>> text;
    ComponentAlignment ca;
};

using ScreenComponentPtr = std::shared_ptr<ScreenComponent>;

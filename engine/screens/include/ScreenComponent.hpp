#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Colours.hpp"
#include "ComponentAlignment.hpp"
#include "Symbol.hpp"

class ScreenComponent
{
  public:
    ScreenComponent();
    ScreenComponent(const std::string& new_text, const std::vector<Symbol>& symbols);
    ScreenComponent(const std::string& new_text, const Colour new_colour, const std::vector<Symbol>& symbols);

    virtual void set_text(const std::vector<std::pair<std::string, Colour>>& new_text);
    virtual void add_text(const std::string& new_text);
    virtual void add_text(const std::string& new_text, const Colour new_colour);
    virtual std::vector<std::pair<std::string, Colour>> get_text() const;

    virtual std::vector<Symbol> get_symbols() const;

    void set_spacing_after(const ComponentAlignment& new_component_alignment);
    ComponentAlignment get_spacing_after() const;

  protected:
    std::vector<std::pair<std::string, Colour>> text;
    std::vector<Symbol> symbols;
    ComponentAlignment ca;
};

using ScreenComponentPtr = std::shared_ptr<ScreenComponent>;

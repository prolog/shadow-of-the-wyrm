#pragma once
#include <vector>
#include <string>
#include "MenuComponent.hpp"

class Option
{
  public:
    Option();
    Option(const int id, const std::string& option_description);

    void set_id(const int new_id);
    int get_id() const;

    void set_description(const std::string& new_description);
    std::string get_description() const;

  protected:
    // May have to map this to another ID in another class.  But for the actual Option object, a
    // numerical value should be OK...
    int id;
    std::string description;
};

class OptionsComponent : public MenuComponent
{
  public:
    OptionsComponent();

    void clear_options();
    void add_option(const Option& additional_option);
    std::vector<Option> get_options() const;

  protected:
    std::vector<Option> options;
};

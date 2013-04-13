#pragma once
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
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

    void clear_option_descriptions();
    void add_option_description(const std::string& additional_description);
    std::vector<std::string> get_option_descriptions() const;

    void set_show_option_descriptions(const bool new_show_option_descriptions);
    bool get_show_option_descriptions() const;

  protected:
    bool show_option_descriptions;
    std::vector<Option> options;
    std::vector<std::string> option_descriptions; // These describe the option at the same index in "options".
};

typedef boost::shared_ptr<OptionsComponent> OptionsComponentPtr;

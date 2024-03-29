#pragma once
#include <vector>
#include <string>
#include <memory>
#include "ScreenComponent.hpp"
#include "TextComponent.hpp"

class Option
{
  public:
    Option();

    void set_colour(const Colour new_colour);
    Colour get_colour() const;

    void set_enabled(const bool new_enabled);
    bool get_enabled() const;

    // A unique identifier within the current set of options.
    // 0, 1, 2, etc.
    void set_id(const int new_id);
    int get_id() const;
    int get_id_for_random() const; // get the '*' random option
    bool is_random_option(const int opt) const;

    // The char to display when displaying the option in the UI - e.g., 'a', 'e'
    char get_id_char() const;

    // An identifier in some other collection.  For example, an option might
    // refer to a particular item, or creature, etc.
    void set_external_id(const std::string& new_external_id);
    std::string get_external_id() const;

    void set_description(const std::string& new_description);
    TextComponentPtr get_description() const;

    void set_uppercase(const bool new_uppercase);
    bool get_uppercase() const;

    void set_property(const std::string& prop, const std::string& val);
    void set_properties(const std::map<std::string, std::string>& new_properties);
    bool has_property(const std::string& prop) const;
    std::string get_property(const std::string& prop) const;
    std::map<std::string, std::string> get_properties() const;

  protected:
    // May have to map this to another ID in another class.  But for the actual Option object, a
    // numerical value should be OK...
    int id;
    std::string external_id;
    TextComponentPtr description;
    Colour colour;
    bool enabled;
    bool uppercase;

    std::map<std::string, std::string> properties;
};

class OptionsComponent : public ScreenComponent
{
  public:
    OptionsComponent();

    void clear_options();
    void add_option(const Option& additional_option);
    std::vector<Option> get_options() const;
    std::vector<Option>& get_options_ref();

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

using OptionsComponentPtr = std::shared_ptr<OptionsComponent>;
using OptionPtr = std::shared_ptr<Option>;

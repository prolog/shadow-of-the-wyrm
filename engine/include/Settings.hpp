#pragma once
#include <boost/property_tree/ptree.hpp>
#include "ISerializable.hpp"

class Settings : public ISerializable
{
  public:
    Settings(const bool read_from_disk = false);

    // This is generally called by passing in a string literal.
    // Ideally, there should be one and only one place in which each setting
    // is actually called for/needed.  If they are needed in multiple locations,
    // consider creating some sort of class to hold all the constants.
    std::string get_setting(const std::string& key) const;
    bool get_setting_as_bool(const std::string& key, const bool default_val = false) const;

    std::map<std::string, std::string> get_settings_starts_with(const std::string& setting_prefix) const;

    // Get all the keybindings (settings whose key starts with "key_")
    std::map<std::string, std::string> get_keybindings() const;

    // Set a particular setting within the ptree.
    void set_setting(const std::string& name, const std::string& val);

    // Set/replace additional settings within the ptree.
    void set_settings(const std::map<std::string, std::string>& addl_settings);

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    boost::property_tree::ptree settings_tree;
    static const std::string SETTINGS_FILENAME;
    static const std::string KEYBINDING_PREFIX;

  private:
    ClassIdentifier internal_class_identifier() const override;
};


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

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    boost::property_tree::ptree settings_tree;
    static const std::string SETTINGS_FILENAME;

  private:
    ClassIdentifier internal_class_identifier() const override;
};


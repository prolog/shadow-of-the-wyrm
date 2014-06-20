#pragma once
#include <boost/property_tree/ptree.hpp>
#include "ISerializable.hpp"

class Settings : public ISerializable
{
  public:
    Settings(const bool read_from_disk = false);

    std::string get_setting(const std::string& key) const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    boost::property_tree::ptree settings_tree;
    static const std::string SETTINGS_FILENAME;

  private:
    ClassIdentifier internal_class_identifier() const override;
};


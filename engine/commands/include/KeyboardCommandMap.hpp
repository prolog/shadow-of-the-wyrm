#pragma once
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include "ISerializable.hpp"

typedef std::map<std::string, std::string> KeyboardCommandMappingMap;

class KeyboardCommandMap : public ISerializable
{
  public:
    KeyboardCommandMap();
    virtual ~KeyboardCommandMap();

    virtual std::string get_command_type(const std::string& keyboard_input);

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

    virtual KeyboardCommandMap* clone();

  protected:
    virtual void command_not_found(const std::string& keyboard_input);
    virtual void initialize_command_mapping();
    KeyboardCommandMappingMap command_mapping;

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<KeyboardCommandMap> KeyboardCommandMapPtr;

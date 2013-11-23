#pragma once
#include <string>
#include <map>
#include <memory>
#include "ISerializable.hpp"

typedef std::map<std::string, std::string> KeyboardCommandMappingMap;

class KeyboardCommandMap : public ISerializable
{
  public:
    KeyboardCommandMap();
    virtual ~KeyboardCommandMap();
    bool operator==(const KeyboardCommandMap& kcm) const;

    virtual std::string get_command_type(const std::string& keyboard_input);

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

    virtual KeyboardCommandMap* clone();

  protected:
    friend class SL_Engine_Commands_KeyboardCommandMapFixture;

    virtual void command_not_found(const std::string& keyboard_input);
    virtual void initialize_command_mapping();
    KeyboardCommandMappingMap command_mapping;

  private:
    ClassIdentifier internal_class_identifier() const;
};

#ifdef UNIT_TESTS
#include "gtest/gtest.h"
// Test fixture declared here so that it can be subclassed in the _test.cpp files
class SL_Engine_Commands_KeyboardCommandMapFixture : public ::testing::Test
{
  public:
    void SetUp();

  protected:
    void initialize_kcm_for_unit_tests(KeyboardCommandMap& kcm);

    KeyboardCommandMap kcm;
};
#endif

typedef std::shared_ptr<KeyboardCommandMap> KeyboardCommandMapPtr;

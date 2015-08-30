#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include "IKeyboardCommandMap.hpp"
#include "Settings.hpp"

using KeyboardCommandMappingMap = std::map<std::string, std::string>;

class KeyboardCommandMap : public ISerializable, public IKeyboardCommandMap
{
  public:
    KeyboardCommandMap();
    virtual ~KeyboardCommandMap();
    bool operator==(const KeyboardCommandMap& kcm) const;

    virtual std::string get_command_type(const std::string& keyboard_input);
    KeyboardCommandMappingMap get_internal_map();

    std::string get_settings_prefix() const override;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

    virtual KeyboardCommandMap* clone();

  protected:
    friend class SL_Engine_Commands_KeyboardCommandMapFixture;

    virtual void command_not_found(const std::string& keyboard_input);
    virtual void initialize_command_mapping(const Settings& settings);
    virtual void initialize_special_key_mappings();
    virtual void parse_keybindings(const Settings& settings, const std::vector<std::string>& remappable_commands);

    KeyboardCommandMappingMap command_mapping;
    std::map<std::string, std::string> special_key_mappings;

  private:
    virtual std::vector<std::string> get_remappable_commands() const;
    ClassIdentifier internal_class_identifier() const override;
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

using KeyboardCommandMapPtr = std::shared_ptr<KeyboardCommandMap>;

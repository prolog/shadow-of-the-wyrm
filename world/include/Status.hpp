#pragma once
#include <string>
#include "ISerializable.hpp"

class Status : public ISerializable
{
  public:
    Status();
    Status(const std::string& new_id, const bool new_value, const int new_danger_level, const std::string& new_source_id);
    bool operator==(const Status& s) const;

    void set_id(const std::string& new_id);
    std::string get_id() const;

    void set_value(const bool new_value);
    bool get_value() const;

    void set_danger_level(const int new_danger_level);
    int get_danger_level() const;

    // Sets the ID of the originating creature, so that if the creature ever
    // dies, experience can be properly given.
    void set_source_id(const std::string& new_source_id);
    std::string get_source_id() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string id;
    bool value;
    int danger_level;
    std::string source_id;

  private:
    ClassIdentifier internal_class_identifier() const override;
};


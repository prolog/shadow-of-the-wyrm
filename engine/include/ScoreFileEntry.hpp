#pragma once
#include "common.hpp"
#include "ISerializable.hpp"

// Represents an entry in the score file.
class ScoreFileEntry : public ISerializable
{
  public:
    ScoreFileEntry();
    ScoreFileEntry(const ulonglong new_score, const std::string& name, const std::string& race_class_abrv);

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

    ulonglong get_score() const;
    std::string get_name() const;
    std::string get_race_class_abrv() const;

  protected:
    ulonglong score;
    std::string name;
    std::string race_class_abrv;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

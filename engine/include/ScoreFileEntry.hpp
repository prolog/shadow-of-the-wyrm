#pragma once
#include "common.hpp"
#include "ISerializable.hpp"

// Represents an entry in the score file.
class ScoreFileEntry : public ISerializable
{
  public:
    ScoreFileEntry();
    ScoreFileEntry(const ulonglong new_score, const std::string& name, const int lvl, const std::string& race_class_abrv);
    bool operator<(const ScoreFileEntry& sfe) const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

    ulonglong get_score() const;
    std::string get_name() const;
    int get_level() const;
    std::string get_race_class_abrv() const;

  protected:
    ulonglong score;
    std::string name;
    int level;
    std::string race_class_abrv;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

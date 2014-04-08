#pragma once
#include "common.hpp"
#include "ISerializable.hpp"

// Represents an entry in the score file.
class ScoreFileEntry : public ISerializable
{
  public:
    ScoreFileEntry();
    ScoreFileEntry(const ulonglong new_score);

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

    ulonglong get_score() const;

  protected:
    ulonglong score;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

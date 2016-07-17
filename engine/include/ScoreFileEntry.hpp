#pragma once
#include "common.hpp"
#include "CreatureFeatures.hpp"
#include "ISerializable.hpp"

// Represents an entry in the score file.
class ScoreFileEntry : public ISerializable
{
  public:
    ScoreFileEntry();
    ScoreFileEntry(const long long new_score, const std::string& name, const std::string& username, const CreatureSex new_sex, const bool is_current_char, const int lvl, const CreatureWin winner, const std::string& race_class_abrv);
    bool operator<(const ScoreFileEntry& sfe) const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

    long long get_score() const;
    std::string get_name() const;
    std::string get_username() const;
    CreatureSex get_sex() const;
    bool get_is_current_char() const;
    int get_level() const;
    CreatureWin get_winner() const;
    std::string get_race_class_abrv() const;

    std::string str(const int score_number) const;

  protected:
    long long score;
    std::string name;
    std::string username;
    CreatureSex sex;
    bool is_current_char;
    int level;
    CreatureWin winner;
    std::string race_class_abrv;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

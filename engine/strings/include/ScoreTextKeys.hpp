#pragma once
#include <string>

// Text keys and messages related to the high scores.
class ScoreTextKeys
{
  public:
    static std::string get_farewell_text_message(const std::string& name);

    static const std::string SCORE_HIGH_SCORES;

  protected:
    ScoreTextKeys();
    ~ScoreTextKeys();

    static const std::string SCORE_FAREWELL_MESSAGE;
};


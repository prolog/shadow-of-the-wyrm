#pragma once
#include "IDescriber.hpp"
#include "Quests.hpp"

class QuestDescriber : public IDescriber
{
  public:
    QuestDescriber(const Quest& new_quest);

    std::string describe() const override;

  protected:
    Quest quest;
};

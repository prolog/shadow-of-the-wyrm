#pragma once
#include <map>
#include "ISerializable.hpp"

// An individual quest, stored within the Quests object on the Game.
class Quest : public ISerializable
{
  public:
    Quest();
    Quest(const std::string& new_quest_id, const std::string& new_quest_title_sid, const std::string& new_questmaster_name_sid, const std::string& new_quest_description_sid);
    bool operator==(const Quest& q) const;

    void set_quest_id(const std::string& new_quest_id);
    std::string get_quest_id() const;

    void set_quest_title_sid(const std::string& new_quest_id);
    std::string get_quest_title_sid() const;

    void set_questmaster_name_sid(const std::string& new_quest_id);
    std::string get_questmaster_name_sid() const;

    void set_quest_description_sid(const std::string& new_quest_id);
    std::string get_quest_description_sid() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string quest_id;
    std::string quest_title_sid;
    std::string questmaster_name_sid;
    std::string quest_description_sid;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using QuestMap = std::map<std::string, Quest>;

// A collection of quests that are in progress, and completed.
class Quests : public ISerializable
{
  public:
    bool operator==(const Quests& q) const;

    // Clear both the in-progress and completed quests.
    //
    // Obviously, this should only be called when it is really needed
    // (e.g., by the serialization code).
    void clear_all_quests();

    // Add a particular quest to the list of in-progress quests.
    void add_new_quest(const std::string& quest_id, const Quest& new_quest);
    bool remove_active_quest(const std::string& quest_id);
    bool is_quest_in_progress(const std::string& quest_id);

    // Move a quest from the in-progress quests to the completed.
    void set_quest_completed(const std::string& quest_id);
    bool is_quest_completed(const std::string& quest_id);

    QuestMap get_in_progress_quests() const;
    QuestMap get_completed_quests() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    bool deserialize_quest_map(std::istream& stream, const size_t num_quests, QuestMap& quest_map);

    QuestMap in_progress_quest_map;
    QuestMap completed_quest_map;

  private:
    ClassIdentifier internal_class_identifier() const override;
};


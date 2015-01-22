#pragma once
#include <map>
#include <string>
#include <memory>
#include <vector>
#include "AlignmentEnums.hpp"
#include "CreatureActions.hpp"
#include "ISerializable.hpp"
#include "WorshipSiteTypes.hpp"
#include "Modifier.hpp"

class Deity : public ISerializable
{
  public:
    Deity();
    virtual ~Deity() {};
    bool operator==(const Deity& d) const;
 
    void set_id(const std::string& new_id);
    std::string get_id() const;

    void set_name_sid(const std::string& new_name_sid);
    std::string get_name_sid() const;
    
    void set_description_sid(const std::string& new_description_sid);
    std::string get_description_sid() const;
    
    void set_short_description_sid(const std::string& new_short_description_sid);
    std::string get_short_description_sid() const;

    void set_anger_message_sid(const std::string& new_anger_message_sid);
    std::string get_anger_message_sid() const;
    
    void set_death_message_sid(const std::string& new_death_message_sid);
    std::string get_death_message_sid() const;
    
    void set_alignment_range(const AlignmentRange new_alignment_range);
    AlignmentRange get_alignment_range() const;

    void set_dislike(const std::string& dislike_key, const bool val);
    bool get_dislike(const std::string& dislike_key) const;
    
    void set_crowning_gifts(const std::vector<std::string>& new_crowning_gifts);
    std::vector<std::string> get_crowning_gifts() const;

    void set_summons(const std::vector<std::string>& new_summons);
    std::vector<std::string> get_summons() const;

    void set_worship_site_type(const WorshipSiteType new_worship_site_type);
    WorshipSiteType get_worship_site_type() const;

    void set_anger_script(const std::string& new_anger_script);
    std::string get_anger_script() const;
    
    void set_initial_modifier(const Modifier& new_initial_modifier);
    Modifier get_initial_modifier() const;

    void set_user_playable(const bool new_user_playable);
    bool get_user_playable() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string id;
    std::string name_sid;
    std::string description_sid;
    std::string short_description_sid;
    std::string anger_message_sid;
    std::string death_message_sid;
    AlignmentRange alignment_range;
    std::vector<std::string> crowning_gifts;
    std::vector<std::string> summons;
    WorshipSiteType worship_site_type;
    std::string anger_script;
    Modifier initial_modifier; // only used for creature creation
    CreatureActions dislikes;
    bool user_playable;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

typedef std::shared_ptr<Deity> DeityPtr;
typedef std::map<std::string, DeityPtr> DeityMap;

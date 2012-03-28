#pragma once
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include "AlignmentEnums.hpp"

class Deity
{
  public:
    Deity();
 
    void set_id(const std::string& new_id);
    std::string get_id() const;

    void set_name_sid(const std::string& new_name_sid);
    std::string get_name_sid() const;
    
    void set_description_sid(const std::string& new_description_sid);
    std::string get_description_sid() const;
    
    void set_short_description_sid(const std::string& new_short_description_sid);
    std::string get_short_description_sid() const;
    
    void set_death_message_sid(const std::string& new_death_message_sid);
    std::string get_death_message_sid() const;
    
    void set_alignment_range(const AlignmentRange new_alignment_range);
    AlignmentRange get_alignment_range() const;

  protected:
    std::string id;
    std::string name_sid;
    std::string description_sid;
    std::string short_description_sid;
    std::string death_message_sid;
    AlignmentRange alignment_range;
};

typedef boost::shared_ptr<Deity> DeityPtr;
typedef std::map<std::string, DeityPtr> DeityMap;

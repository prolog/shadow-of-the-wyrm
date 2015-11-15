#pragma once
#include <string>
#include "CreatureFeatures.hpp"

// Encapsulates the sex, race, class, and deity selected at the
// new game screen.  These can be user-selected (as when the user selects
// "new game"), or randomly selected, as when the user opts for full or
// partial random creation.
class CharacterCreationDetails
{
  public:
    CharacterCreationDetails();
    CharacterCreationDetails(const CreatureSex cs, const std::string& r_id, const std::string& c_id, const std::string& d_id);

    void set_sex(const CreatureSex new_sex);
    CreatureSex get_sex() const;

    void set_race_id(const std::string& new_race_id);
    std::string get_race_id() const;

    void set_class_id(const std::string& new_class_id);
    std::string get_class_id() const;

    void set_deity_id(const std::string& new_deity_id);
    std::string get_deity_id() const;

  protected:
    CreatureSex sex;
    std::string race_id;
    std::string class_id;
    std::string deity_id;
};


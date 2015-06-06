#pragma once
#include <string>
#include <map>
#include <vector>

// Encapsulates a number of values both necessary and optional for
// creature generation.  ID is required, and a hostility map is also
// provided so friendly creatures can be generated hostile to the player
// (or other creatures!).
class CreatureGenerationOptions
{
  public:
    void set_id(const std::string& new_id);
    std::string get_id() const;

    void set_hostility(const std::string& creature_id, const bool value);
    void set_hostility(const std::map<std::string, bool>& new_hostility);
    std::map<std::string, bool> get_hostility_map() const;
    bool get_hostility(const std::string& creature_id) const;

    bool parse(const std::string& parse_string);

  protected:
    void process_options(const std::vector<std::pair<std::string, std::string>>& options);
    bool parse_hostility(const std::string& parse_string);

    std::string id;
    std::map<std::string, bool> hostility;
};


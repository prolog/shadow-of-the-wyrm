// Prototypes for global functions
#include <string>
#include "Colours.hpp"

std::string get_version();
std::string get_code_name();
std::string get_game_version_synopsis();
std::string get_compiler_details();
std::string get_title_poem();
std::string convert_colour_to_hex_code(const Colours colour);
std::string html_encode(const std::string& str);

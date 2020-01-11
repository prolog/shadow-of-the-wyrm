// Prototypes for global functions
#pragma once
#include <string>
#include "Colours.hpp"

std::string get_title_poem();
std::string convert_colour_to_hex_code(const Colours colour);
std::string html_encode(const std::string& str);
size_t count_substrings(const std::string& text, const std::string& substring);
bool dequal(const double, const double);
bool fequal(const float, const float);

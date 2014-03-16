#pragma once
#include <set>
#include "OptionsComponent.hpp"

// Wrapper for Curses menu/item data, mostly to allow easy deletion
// during program flow.

class MenuWrapper
{
  public:
    MenuWrapper();
    
    int get_num_items() const;

    bool has_options() const;
    void add_options(OptionsComponentPtr options);
    void add_option(const char option);
    bool is_option_in_set(const char option) const;

  protected:
    std::set<char> options;
};
